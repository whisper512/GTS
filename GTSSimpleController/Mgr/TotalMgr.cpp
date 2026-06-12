#include "TotalMgr.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QCoreApplication>

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
    // 从json读取配置
    if (!loadScaleFromJson()) {
        readScaleFromBoard();
        saveScaleToJson();
    }
    else {
        saveScaleToJson();
    }
    // 读取DAC配置
    readDacConfig();
    // 读取control误差极限
    readFollowErrorLimit();
    // 读取profile停止减速度参数
    readStopDecel();

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


// ============================================================
//                    轴当量 JSON 读写
// ============================================================

QString CTotalMgr::scaleJsonPath() const
{
    return QCoreApplication::applicationDirPath() + QStringLiteral("/axis_scale.json");
}

bool CTotalMgr::loadScaleFromJson(const QString& filePath)
{
    QString path = filePath.isEmpty() ? scaleJsonPath() : filePath;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject())
        return false;

    QJsonObject root = doc.object();
    QJsonArray axes = root.value(QStringLiteral("axes")).toArray();

    // 先全部置默认值
    for (int i = 0; i < m_axisCount; ++i) {
        m_cfg.profileScale[i] = stuScaleFactor{ 1, 1 };
        m_cfg.encScale[i] = stuScaleFactor{ 1, 1 };
    }

    for (int i = 0; i < axes.size() && i < m_axisCount; ++i) {
        QJsonObject obj = axes[i].toObject();
        int axis = obj.value(QStringLiteral("axis")).toInt(0);
        if (axis < 1 || axis > m_axisCount)
            continue;

        int idx = axis - 1;

        QJsonObject prf = obj.value(QStringLiteral("profile")).toObject();
        if (!prf.isEmpty()) {
            m_cfg.profileScale[idx].alpha = static_cast<long>(prf.value(QStringLiteral("alpha")).toDouble(1.0));
            m_cfg.profileScale[idx].beta = static_cast<long>(prf.value(QStringLiteral("beta")).toDouble(1.0));
        }

        QJsonObject enc = obj.value(QStringLiteral("encoder")).toObject();
        if (!enc.isEmpty()) {
            m_cfg.encScale[idx].alpha = static_cast<long>(enc.value(QStringLiteral("alpha")).toDouble(1.0));
            m_cfg.encScale[idx].beta = static_cast<long>(enc.value(QStringLiteral("beta")).toDouble(1.0));
        }
        else {
            // 未配置 encoder → 默认与 profile 一致
            m_cfg.encScale[idx] = m_cfg.profileScale[idx];
        }
    }
    return true;
}

bool CTotalMgr::saveScaleToJson(const QString& filePath) const
{
    QString path = filePath.isEmpty() ? scaleJsonPath() : filePath;

    QJsonArray axes;
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        const stuScaleFactor& prf = m_cfg.profileScale[idx];
        const stuScaleFactor& enc = m_cfg.encScale[idx];

        QJsonObject prfObj;
        prfObj[QStringLiteral("alpha")] = static_cast<qint64>(prf.alpha);
        prfObj[QStringLiteral("beta")] = static_cast<qint64>(prf.beta); 

        QJsonObject encObj;
        encObj[QStringLiteral("alpha")] = static_cast<qint64>(enc.alpha);
        encObj[QStringLiteral("beta")] = static_cast<qint64>(enc.beta);

        QJsonObject obj;
        obj[QStringLiteral("axis")] = axis;
        obj[QStringLiteral("profile")] = prfObj;
        obj[QStringLiteral("encoder")] = encObj;

        axes.append(obj);
    }

    QJsonObject root;
    root[QStringLiteral("version")] = 1;
    root[QStringLiteral("axes")] = axes;

    QDir().mkpath(QFileInfo(path).absolutePath());

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}


void CTotalMgr::readScaleFromBoard()
{
    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int idx = axis - 1;
        stuScaleFactor& prf = m_cfg.profileScale[idx];
        stuScaleFactor& enc = m_cfg.encScale[idx];

        // 读规划器当量
        m_axisMgr->getProfileScale(axis, prf.alpha, prf.beta);

        // 读编码器当量
        short ret = m_axisMgr->getEncoderScale(axis, enc.alpha, enc.beta);
        if (ret != 0) {
            // 卡不支持 → 编码器当量 = 规划器当量
            enc = prf;
        }
    }
}

// ============================================================
//                    读写接口
// ============================================================

void CTotalMgr::setProfileScale(short axis, long alpha, long beta)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_cfg.profileScale[idx] = { alpha, beta };
    m_axisMgr->setProfileScale(axis, alpha, beta);
}

long CTotalMgr::profileScaleAlpha(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.profileScale[axis - 1].alpha : 1;
}

long CTotalMgr::profileScaleBeta(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.profileScale[axis - 1].beta : 1;
}

void CTotalMgr::setEncoderScale(short axis, long alpha, long beta)
{
    if (axis < 1 || axis > m_axisCount) return;
    int idx = axis - 1;
    m_cfg.encScale[idx] = { alpha, beta };
    m_axisMgr->setEncoderScale(axis, alpha, beta);
}

long CTotalMgr::encoderScaleAlpha(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.encScale[axis - 1].alpha : 1;
}

long CTotalMgr::encoderScaleBeta(short axis) const
{
    return (axis >= 1 && axis <= m_axisCount) ? m_cfg.encScale[axis - 1].beta : 1;
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
