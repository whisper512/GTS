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
    //initStopIO(); 
    // 读取GPI配置
    initGpiSense();
    // 读取step
    initStepPulseMode();
    // 读取编码器配置
    initEncoderConfig();
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
            m_cfg.alarmAvailable[idx] = true;
            m_cfg.alarmActive[idx] = true;
        }
        else {
            m_cfg.alarmAvailable[idx] = false;
            m_cfg.alarmActive[idx] = false;
        }
    }
}

bool CTotalMgr::toggleAlarm(short axis)
{
    if (axis < 1 || axis > m_axisCount) return false;
    int idx = axis - 1;
    if (!m_cfg.alarmAvailable[idx]) return false;

    short ret;
    if (m_cfg.alarmActive[idx]) {
        ret = GtsHal::alarmOff(axis);
    }
    else {
        ret = GtsHal::alarmOn(axis);
    }
    if (ret == 0) {
        m_cfg.alarmActive[idx] = !m_cfg.alarmActive[idx];
    }
    return m_cfg.alarmActive[idx];
}

bool CTotalMgr::isAlarmActive(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.alarmActive[axis - 1] : false;
}

bool CTotalMgr::isAlarmAvailable(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.alarmAvailable[axis - 1] : false;
}

void CTotalMgr::initLimitState()
{
    QString log;
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        GtsHal::lmtsOff(axis, -1);
        short ret = GtsHal::lmtsOn(axis, -1);
        if (ret == 0) {
            m_cfg.limitAvailable[idx] = true;
            m_cfg.limitActive[idx] = true;
        }
        else {
            m_cfg.limitAvailable[idx] = false;
            m_cfg.limitActive[idx] = false;
        }
        log += QStringLiteral("轴%1: ret=%2 | available=%3 | active=%4\n")
            .arg(axis)
            .arg(ret)
            .arg(m_cfg.limitAvailable[idx] ? "true" : "false")
            .arg(m_cfg.limitActive[idx] ? "true" : "false");
    }
}

bool CTotalMgr::toggleLimit(short axis)
{
    if (axis < 1 || axis > m_axisCount) return false;
    int idx = axis - 1;
    if (!m_cfg.limitAvailable[idx]) return false;

    short ret;
    if (m_cfg.limitActive[idx]) {
        ret = GtsHal::lmtsOff(axis, -1);
    }
    else {
        ret = GtsHal::lmtsOn(axis, -1);
    }
    if (ret == 0) {
        m_cfg.limitActive[idx] = !m_cfg.limitActive[idx];
    }
    return m_cfg.limitActive[idx];
}

bool CTotalMgr::isLimitActive(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.limitActive[axis - 1] : false;
}

bool CTotalMgr::isLimitAvailable(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.limitAvailable[axis - 1] : false;
}

void CTotalMgr::readScaleEquivalents()
{
    QString log;

    // 规划器当量
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        long alpha = 1, beta = 1;
        short ret = GtsHal::getProfileScale(axis, &alpha, &beta);
        m_cfg.profileScaleAlpha[idx] = alpha;
        m_cfg.profileScaleBeta[idx] = beta;
    }
}


void CTotalMgr::setProfileScale(short axis, long alpha, long beta)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_cfg.profileScaleAlpha[idx] = alpha;
    m_cfg.profileScaleBeta[idx] = beta;
    GtsHal::setProfileScale(axis, alpha, beta);
}

void CTotalMgr::setEncoderScale(short encoder, long alpha, long beta)
{
    if (encoder < 1 || encoder > 8) return;
    int idx = encoder - 1;
    m_cfg.encScaleAlpha[idx] = alpha;
    m_cfg.encScaleBeta[idx] = beta;
    GtsHal::setEncoderScale(encoder, alpha, beta);
}

long CTotalMgr::profileScaleAlpha(short axis) const {
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.profileScaleAlpha[axis - 1] : 1;
}
long CTotalMgr::profileScaleBeta(short axis) const {
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.profileScaleBeta[axis - 1] : 1;
}
long CTotalMgr::encScaleAlpha(short encoder) const {
    return (encoder >= 1 && encoder <= m_axisCount) ? m_cfg.encScaleAlpha[encoder - 1] : 1;
}
long CTotalMgr::encScaleBeta(short encoder) const {
    return (encoder >= 1 && encoder <= m_axisCount) ? m_cfg.encScaleBeta[encoder - 1] : 1;
}

void CTotalMgr::readDacConfig()
{
    for (short dac = 1; dac <= m_axisCount; ++dac) {
        int idx = dac - 1;
        m_cfg.dacBias[idx] = m_axisMgr->getDacBias(dac);
        m_cfg.dacLimit[idx] = m_axisMgr->getDacLimit(dac);
    }
}

void CTotalMgr::setDacBias(short dac, short bias)
{
    if (dac < 1 || dac > m_axisCount) return;
    int idx = dac - 1;
    m_cfg.dacBias[idx] = bias;
    m_axisMgr->setDacBias(dac, bias);
}

void CTotalMgr::setDacLimit(short dac, short limit)
{
    if (dac < 1 || dac > m_axisCount) return;
    int idx = dac - 1;
    m_cfg.dacLimit[idx] = limit;
    m_axisMgr->setDacLimit(dac, limit);
}

short CTotalMgr::dacBias(short dac) const
{
    return (dac >= 1 && dac <= m_axisCount) ? m_cfg.dacBias[dac - 1] : 0;
}

short CTotalMgr::dacLimit(short dac) const
{
    return (dac >= 1 && dac <= m_axisCount) ? m_cfg.dacLimit[dac - 1] : 32767;
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
        m_cfg.followingErrorLimit[idx] = m_axisMgr->getFollowErrorLimit(ctrl);
    }
}

void CTotalMgr::setFollowErrorLimit(short control, long error)
{
    if (control < 1 || control > m_axisCount) return;
    int idx = control - 1;
    m_cfg.followingErrorLimit[idx] = error;
    m_axisMgr->setFollowErrorLimit(control, error);
}

long CTotalMgr::followErrorLimit(short control) const
{
    return (control >= 1 && control <= m_axisCount) ? m_cfg.followingErrorLimit[control - 1] : 32767;
}

void CTotalMgr::readStopDecel()
{
    for (short profile = 1; profile <= m_axisCount; ++profile) {
        int idx = profile - 1;
        double smooth = 100.0, abrupt = 1000.0;
        m_axisMgr->getStopDecel(profile, smooth, abrupt);
        m_cfg.smoothStopDec[idx] = smooth;
        m_cfg.estopDec[idx] = abrupt;
    }
}

void CTotalMgr::setStopDecel(short profile, double smooth, double abrupt)
{
    if (profile < 1 || profile > m_axisCount) return;
    int idx = profile - 1;
    m_cfg.smoothStopDec[idx] = smooth;
    m_cfg.estopDec[idx] = abrupt;
    m_axisMgr->setStopDecel(profile, smooth, abrupt);
}

double CTotalMgr::smoothStopDec(short profile) const
{
    return (profile >= 1 && profile <= m_axisCount) ? m_cfg.smoothStopDec[profile - 1] : 100.0;
}

double CTotalMgr::estopDec(short profile) const
{
    return (profile >= 1 && profile <= m_axisCount) ? m_cfg.estopDec[profile - 1] : 1000.0;
}

void CTotalMgr::initAxisCtrlMode()
{
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        m_cfg.axisCtrlMode[idx] = 0;
        m_axisMgr->setControlMode(axis, 0);
    }
}

void CTotalMgr::setAxisCtrlMode(short axis, short mode)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_cfg.axisCtrlMode[idx] = mode;
    m_axisMgr->setControlMode(axis, mode);
}

short CTotalMgr::axisCtrlMode(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.axisCtrlMode[axis - 1] : 0;
}

void CTotalMgr::initStopIO()
{
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        // 急停
        m_axisMgr->setStopIO(axis, 0, m_cfg.stopInputType[idx][0], m_cfg.stopInputIndex[idx][0]);
        // 平滑停止
        m_axisMgr->setStopIO(axis, 1, m_cfg.stopInputType[idx][1], m_cfg.stopInputIndex[idx][1]);
    }
}

void CTotalMgr::setStopIO(short axis, short stopType, short inputType, short inputIndex)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_cfg.stopInputType[idx][stopType] = inputType;
    m_cfg.stopInputIndex[idx][stopType] = inputIndex;
    m_axisMgr->setStopIO(axis, stopType, inputType, inputIndex);
}

short CTotalMgr::stopInputType(short axis, short stopType) const
{
    if (axis < 1 || axis > m_axisCount) return 0;
    return m_cfg.stopInputType[axis - 1][stopType];
}

short CTotalMgr::stopInputIndex(short axis, short stopType) const
{
    if (axis < 1 || axis > m_axisCount) return 1;
    return m_cfg.stopInputIndex[axis - 1][stopType];
}

void CTotalMgr::initGpiSense()
{
    m_cfg.gpiSense = 0;
    m_ioMgr->setGpiSense(0);   // 默认全部不取反
}

void CTotalMgr::setGpiSenseBit(short diIndex, bool invert)
{
    if (diIndex < 1 || diIndex > 16) return;

    if (invert) {
        m_cfg.gpiSense |= (1 << (diIndex - 1));
    }
    else {
        m_cfg.gpiSense &= ~(1 << (diIndex - 1));
    }
    m_ioMgr->setGpiSense(m_cfg.gpiSense);
}

bool CTotalMgr::isGpiSenseInvert(short diIndex) const
{
    if (diIndex < 1 || diIndex > 16) return false;
    return (m_cfg.gpiSense >> (diIndex - 1)) & 1;
}

unsigned short CTotalMgr::gpiSense() const
{
    return m_cfg.gpiSense;
}

void CTotalMgr::initStepPulseMode()
{
    for (short step = 1; step <= m_axisCount; ++step) {
        int idx = step - 1;
        m_cfg.stepPulseMode[idx] = 0;
        m_axisMgr->setStepPulseDir(step);
    }
}

void CTotalMgr::setStepPulseMode(short step, short mode)
{
    if (step < 1 || step > m_axisCount) return;
    int idx = step - 1;
    m_cfg.stepPulseMode[idx] = mode;
    if (mode == 0) {
        m_axisMgr->setStepPulseDir(step);
    }
    else {
        m_axisMgr->setStepPulseCCW(step);
    }
}

short CTotalMgr::stepPulseMode(short step) const
{
    return (step >= 1 && step <= m_axisCount) ? m_cfg.stepPulseMode[step - 1] : 0;
}

void CTotalMgr::initEncoderConfig()
{
    unsigned short sense = 0;   // 默认全部正常
    m_feedbackMgr->setEncoderSense(sense);

    for (short enc = 1; enc <= m_axisCount; ++enc) {
        int idx = enc - 1;
        m_cfg.encInvert[idx] = false;
        m_cfg.encIsPulse[idx] = false;
        m_feedbackMgr->encoderOn(idx);   // idx 是 0-based
    }
}

void CTotalMgr::setEncoderInvert(short encoder, bool invert)
{
    if (encoder < 1 || encoder > m_axisCount) return;
    int idx = encoder - 1;
    m_cfg.encInvert[idx] = invert;

    // 重建全局 sense 位掩码
    unsigned short sense = 0;
    for (short i = 0; i < m_axisCount; ++i) {
        if (m_cfg.encInvert[i]) sense |= (1 << i);
    }
    m_feedbackMgr->setEncoderSense(sense);
}

void CTotalMgr::setEncoderPulseCount(short encoder, bool isPulse)
{
    if (encoder < 1 || encoder > m_axisCount) return;
    int idx = encoder - 1;
    m_cfg.encIsPulse[idx] = isPulse;

    if (isPulse) {
        m_feedbackMgr->encoderOff(idx);    // 关闭编码器 = 脉冲计数器模式
    }
    else {
        m_feedbackMgr->encoderOn(idx);     // 开启编码器
    }
}

bool CTotalMgr::encoderInvert(short encoder) const
{
    return (encoder >= 1 && encoder <= m_axisCount) ? m_cfg.encInvert[encoder - 1] : false;
}

bool CTotalMgr::encoderPulseCount(short encoder) const
{
    return (encoder >= 1 && encoder <= m_axisCount) ? m_cfg.encIsPulse[encoder - 1] : false;
}
