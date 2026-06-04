#include "TotalMgr.h"
#include <QMessageBox>

CTotalMgr::CTotalMgr(QObject* parent)
    : QObject(parent)
    , m_vecAxis(m_axisCount)
{
    // 初始化各个模块
    m_boardMgr = std::make_unique<BoardMgr>(this);
    m_axisMgr = std::make_unique<AxisMgr>(this);
    m_motionMgr = std::make_unique<MotionMgr>(this);
    m_interpolationMgr = std::make_unique<InterpolationMgr>(this);
    m_ioMgr = std::make_unique<IOMgr>(this);
    m_feedbackMgr = std::make_unique<FeedbackMgr>(this);
    m_configMgr = std::make_unique<ConfigMgr>(this);

    // 创建定时器用来刷新实时数据
    m_pRefreshTimer = new QTimer(this);
    connect(m_pRefreshTimer, &QTimer::timeout, this, &CTotalMgr::onRefreshTimeout);
}

CTotalMgr::~CTotalMgr() {
    stopRefresh();
}

void CTotalMgr::startRefresh(int intervalMs)
{
    if (m_pRefreshTimer->isActive()) {
        m_pRefreshTimer->stop();
    }
    // 立即刷新一次 
    onRefreshTimeout();
    // 启动定时器
    m_pRefreshTimer->start(intervalMs);
}

void CTotalMgr::stopRefresh()
{
    m_pRefreshTimer->stop();
}

void CTotalMgr::initAfterBoardOpened()
{
    // 启动定时器开始实时获取数据
    startRefresh();

    // 初始化轴报警状态
    initAlarmState();
    // 初始化轴限位状态
    initLimitState();
    // 读取规划器和编码器的当量
    readScaleEquivalents();
    // 读取DAC配置
    readDacConfig();
    // 读取误差极限
    readFollowErrorLimit();
    // 读取停止减速度参数
    readStopDecel();
    // 读取轴控制模式
    initAxisCtrlMode();
    // 读取停止IO设置
    initStopIO();
    // 读取GPI配置
    initGpiSense();
    emit configChanged();

    //读取运动参数
    m_motionMgr->getCommonMotionInfo(m_vecAxis);
    emit axisSettingUpdated(m_vecAxis);

}

void CTotalMgr::cleanupAfterBoardClosed()
{
    stopRefresh();
    m_vecAxis.clear();     // 清空轴数据
    m_clocks = stuClock(); // 清空时钟
}

void CTotalMgr::initAlarmState()
{
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        GtsHal::alarmOff(axis);
        short ret = GtsHal::alarmOn(axis);
        if (ret == 0) {
            m_alarmAvailable[idx] = true;
            m_alarmActive[idx] = true;
        }
        else {
            m_alarmAvailable[idx] = false;
            m_alarmActive[idx] = false;
        }
    }
}

bool CTotalMgr::toggleAlarm(short axis)
{
    if (axis < 1 || axis > m_axisCount) return false;
    int idx = axis - 1;
    if (!m_alarmAvailable[idx]) return false;

    short ret;
    if (m_alarmActive[idx]) {
        ret = GtsHal::alarmOff(axis);
    }
    else {
        ret = GtsHal::alarmOn(axis);
    }
    if (ret == 0) {
        m_alarmActive[idx] = !m_alarmActive[idx];
    }
    return m_alarmActive[idx];
}

bool CTotalMgr::isAlarmActive(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_alarmActive[axis - 1] : false;
}

bool CTotalMgr::isAlarmAvailable(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_alarmAvailable[axis - 1] : false;
}

void CTotalMgr::initLimitState()
{
    QString log;
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        GtsHal::lmtsOff(axis, -1);
        short ret = GtsHal::lmtsOn(axis, -1);
        if (ret == 0) {
            m_limitAvailable[idx] = true;
            m_limitActive[idx] = true;
        }
        else {
            m_limitAvailable[idx] = false;
            m_limitActive[idx] = false;
        }
        log += QStringLiteral("轴%1: ret=%2 | available=%3 | active=%4\n")
            .arg(axis)
            .arg(ret)
            .arg(m_limitAvailable[idx] ? "true" : "false")
            .arg(m_limitActive[idx] ? "true" : "false");
    }
}

bool CTotalMgr::toggleLimit(short axis)
{
    if (axis < 1 || axis > m_axisCount) return false;
    int idx = axis - 1;
    if (!m_limitAvailable[idx]) return false;

    short ret;
    if (m_limitActive[idx]) {
        ret = GtsHal::lmtsOff(axis, -1);
    }
    else {
        ret = GtsHal::lmtsOn(axis, -1);
    }
    if (ret == 0) {
        m_limitActive[idx] = !m_limitActive[idx];
    }
    return m_limitActive[idx];
}

bool CTotalMgr::isLimitActive(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_limitActive[axis - 1] : false;
}

bool CTotalMgr::isLimitAvailable(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_limitAvailable[axis - 1] : false;
}

void CTotalMgr::readScaleEquivalents()
{
    QString log;

    // 规划器当量
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        long alpha = 1, beta = 1;
        short ret = GtsHal::getProfileScale(axis, &alpha, &beta);
        m_profileScaleAlpha[idx] = alpha;
        m_profileScaleBeta[idx] = beta;
    }
}


void CTotalMgr::setProfileScale(short axis, long alpha, long beta)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_profileScaleAlpha[idx] = alpha;
    m_profileScaleBeta[idx] = beta;
    GtsHal::setProfileScale(axis, alpha, beta);
}

void CTotalMgr::setEncoderScale(short encoder, long alpha, long beta)
{
    if (encoder < 1 || encoder > 8) return;
    int idx = encoder - 1;
    m_encScaleAlpha[idx] = alpha;
    m_encScaleBeta[idx] = beta;
    GtsHal::setEncoderScale(encoder, alpha, beta);
}

long CTotalMgr::profileScaleAlpha(short axis) const {
    return (axis >= 1 && axis <= m_axisCount) ? m_profileScaleAlpha[axis - 1] : 1;
}
long CTotalMgr::profileScaleBeta(short axis) const {
    return (axis >= 1 && axis <= m_axisCount) ? m_profileScaleBeta[axis - 1] : 1;
}
long CTotalMgr::encScaleAlpha(short encoder) const {
    return (encoder >= 1 && encoder <= m_axisCount) ? m_encScaleAlpha[encoder - 1] : 1;
}
long CTotalMgr::encScaleBeta(short encoder) const {
    return (encoder >= 1 && encoder <= m_axisCount) ? m_encScaleBeta[encoder - 1] : 1;
}

void CTotalMgr::readDacConfig()
{
    for (short dac = 1; dac <= m_axisCount; ++dac) {
        int idx = dac - 1;
        m_dacBias[idx] = m_axisMgr->getDacBias(dac);
        m_dacLimit[idx] = m_axisMgr->getDacLimit(dac);
    }
}

void CTotalMgr::setDacBias(short dac, short bias)
{
    if (dac < 1 || dac > m_axisCount) return;
    int idx = dac - 1;
    m_dacBias[idx] = bias;
    m_axisMgr->setDacBias(dac, bias);
}

void CTotalMgr::setDacLimit(short dac, short limit)
{
    if (dac < 1 || dac > m_axisCount) return;
    int idx = dac - 1;
    m_dacLimit[idx] = limit;
    m_axisMgr->setDacLimit(dac, limit);
}

short CTotalMgr::dacBias(short dac) const
{
    return (dac >= 1 && dac <= m_axisCount) ? m_dacBias[dac - 1] : 0;
}

short CTotalMgr::dacLimit(short dac) const
{
    return (dac >= 1 && dac <= m_axisCount) ? m_dacLimit[dac - 1] : 32767;
}


void CTotalMgr::onRefreshTimeout()
{
    if (!m_boardMgr->isOpen()) return;

    // 读取板卡时钟
    m_clocks = m_boardMgr->getClocks();
    emit boardClockUpdated(m_clocks);

    // 读取轴状态信息
    m_axisMgr->getAxisStatusInfo(m_vecAxis);
    m_motionMgr->getAxisMotionInfo(m_vecAxis);
    emit axisUpdated(m_vecAxis);

    // 读取IO状态信息
    m_ioMgr->getPLimitDI(m_di.vecPLimit);
    m_ioMgr->getNLimitDI(m_di.vecNLimit);
    m_ioMgr->getDriverAlarmDI(m_di.vecAlarm);
    m_ioMgr->getHomeDI(m_di.vecHome);
    m_ioMgr->getGPI(m_di.vecGPI);
    m_ioMgr->getArriveDI(m_di.vecArrive);
    m_ioMgr->getHandwheelDI(m_di.vecHandwheel);
    emit diUpdated(m_di);

    // 读取DO状态信息
    m_ioMgr->getMotorEnableDO(m_do.vecServoOn);
    m_ioMgr->getGPO(m_do.vecGPO);
    m_ioMgr->getClearAlarmDO(m_do.vecAlmClear);
    emit doUpdated(m_do);

}

void CTotalMgr::readFollowErrorLimit()
{
    for (short ctrl = 1; ctrl <= m_axisCount; ++ctrl) {
        int idx = ctrl - 1;
        m_followingErrorLimit[idx] = m_axisMgr->getFollowErrorLimit(ctrl);
    }
}

void CTotalMgr::setFollowErrorLimit(short control, long error)
{
    if (control < 1 || control > m_axisCount) return;
    int idx = control - 1;
    m_followingErrorLimit[idx] = error;
    m_axisMgr->setFollowErrorLimit(control, error);
}

long CTotalMgr::followErrorLimit(short control) const
{
    return (control >= 1 && control <= m_axisCount) ? m_followingErrorLimit[control - 1] : 32767;
}

void CTotalMgr::readStopDecel()
{
    for (short profile = 1; profile <= m_axisCount; ++profile) {
        int idx = profile - 1;
        double smooth = 100.0, abrupt = 1000.0;
        m_axisMgr->getStopDecel(profile, smooth, abrupt);
        m_smoothStopDec[idx] = smooth;
        m_estopDec[idx] = abrupt;
    }
}

void CTotalMgr::setStopDecel(short profile, double smooth, double abrupt)
{
    if (profile < 1 || profile > m_axisCount) return;
    int idx = profile - 1;
    m_smoothStopDec[idx] = smooth;
    m_estopDec[idx] = abrupt;
    m_axisMgr->setStopDecel(profile, smooth, abrupt);
}

double CTotalMgr::smoothStopDec(short profile) const
{
    return (profile >= 1 && profile <= m_axisCount) ? m_smoothStopDec[profile - 1] : 100.0;
}

double CTotalMgr::estopDec(short profile) const
{
    return (profile >= 1 && profile <= m_axisCount) ? m_estopDec[profile - 1] : 1000.0;
}

void CTotalMgr::initAxisCtrlMode()
{
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        m_axisCtrlMode[idx] = 0;
        m_axisMgr->setControlMode(axis, 0);
    }
}

void CTotalMgr::setAxisCtrlMode(short axis, short mode)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_axisCtrlMode[idx] = mode;
    m_axisMgr->setControlMode(axis, mode);
}

short CTotalMgr::axisCtrlMode(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_axisCtrlMode[axis - 1] : 0;
}

void CTotalMgr::initStopIO()
{
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        // 急停
        m_axisMgr->setStopIO(axis, 0, m_stopInputType[idx][0], m_stopInputIndex[idx][0]);
        // 平滑停止
        m_axisMgr->setStopIO(axis, 1, m_stopInputType[idx][1], m_stopInputIndex[idx][1]);
    }
}

void CTotalMgr::setStopIO(short axis, short stopType, short inputType, short inputIndex)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_stopInputType[idx][stopType] = inputType;
    m_stopInputIndex[idx][stopType] = inputIndex;
    m_axisMgr->setStopIO(axis, stopType, inputType, inputIndex);
}

short CTotalMgr::stopInputType(short axis, short stopType) const
{
    if (axis < 1 || axis > m_axisCount) return 0;
    return m_stopInputType[axis - 1][stopType];
}

short CTotalMgr::stopInputIndex(short axis, short stopType) const
{
    if (axis < 1 || axis > m_axisCount) return 1;
    return m_stopInputIndex[axis - 1][stopType];
}

void CTotalMgr::initGpiSense()
{
    m_gpiSense = 0;
    m_ioMgr->setGpiSense(0);   // 默认全部不取反
}

void CTotalMgr::setGpiSenseBit(short diIndex, bool invert)
{
    if (diIndex < 1 || diIndex > 16) return;

    if (invert) {
        m_gpiSense |= (1 << (diIndex - 1));
    }
    else {
        m_gpiSense &= ~(1 << (diIndex - 1));
    }
    m_ioMgr->setGpiSense(m_gpiSense);
}

bool CTotalMgr::isGpiSenseInvert(short diIndex) const
{
    if (diIndex < 1 || diIndex > 16) return false;
    return (m_gpiSense >> (diIndex - 1)) & 1;
}

unsigned short CTotalMgr::gpiSense() const
{
    return m_gpiSense;
}
