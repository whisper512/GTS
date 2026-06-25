#include "TotalMgr.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>

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
    m_configMgr->initAxisConfig(&m_cfg, m_axisCount, m_axisMgr.get());

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
    // 从 JSON 加载配置（通过 ConfigMgr）
    if (!m_configMgr->loadAxisConfig()) {
        m_configMgr->readAllAxisConfigFromBoard();
        m_configMgr->saveAxisConfig();
    }
    else {
        m_configMgr->applyAllAxisConfigToBoard();
    }
    // 读取DAC配置
    m_configMgr->readDacConfig();
    // 读取control误差极限
    m_configMgr->readFollowErrorLimit();
    // 读取profile停止减速度参数
    m_configMgr->readStopDecel();

    emit m_configMgr->configChanged();

    // 读取运动参数
    m_motionMgr->getCommonMotionInfo(m_vecAxis);
    emit axisSettingUpdated(m_vecAxis);


    // 同时看一下每个轴的 homeInit 返回值
    for (short i = 1; i <= m_axisCount; ++i) {
        short err = GtsHal::homeInit();  // 直接看返回值
        qDebug() << "axis" << i << "homeInit ret:" << err;
    }
}

void CTotalMgr::cleanupAfterBoardClosed()
{
    stopRefresh();
    m_vecAxis.clear();     // 清空轴数据
    m_clocks = stuClock(); // 清空时钟
}

double CTotalMgr::pulsePerMm(short profile) const
{
    long alpha = configMgr()->profileScaleAlpha(profile);
    long beta = configMgr()->profileScaleBeta(profile);
    if (beta == 0) return 0.0;
    return static_cast<double>(alpha) / beta;
}

long CTotalMgr::mmToPulse(short profile, double mm) const
{
    return static_cast<long>(mm * pulsePerMm(profile));
}

double CTotalMgr::mmpsToPulsePerMs(short profile, double mmps) const
{
    return mmps * pulsePerMm(profile) / 1000.0;       // mm/s → pulse/ms
}

double CTotalMgr::mmps2ToPulsePerMs2(short profile, double mmps2) const
{
    return mmps2 * pulsePerMm(profile) / 1000000.0;   // mm/s² → pulse/ms²
}

double CTotalMgr::pulseToMm(short profile, long pulse) const
{
    double ppm = pulsePerMm(profile);
    if (ppm == 0.0) return 0.0;
    return static_cast<double>(pulse) / ppm;
}

void CTotalMgr::onRefreshTimeout()
{
    if (!m_boardMgr->isOpen()) return;

    // 读取板卡时钟
    m_clocks = m_boardMgr->getClocks();
    emit boardClockUpdated(m_clocks);

    // 读取轴状态信息
    m_axisMgr->getAxisStatusAndMotionInfo(m_vecAxis);
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
