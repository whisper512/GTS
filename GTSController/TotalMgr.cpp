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
