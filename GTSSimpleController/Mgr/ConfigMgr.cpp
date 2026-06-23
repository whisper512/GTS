#include <QJsonDocument>             
#include <QJsonObject>               
#include <QJsonArray>                
#include <QFile>                     
#include <QDir>                      
#include <QCoreApplication>          

#include "ConfigMgr.h"
#include "AxisMgr.h"


ConfigMgr::ConfigMgr(QObject* parent)
    : QObject(parent)
{
}

ConfigMgr::~ConfigMgr() {
}

bool ConfigMgr::isValidAxis(short axis) const {
    return (axis >= 0 && axis < 8);
}

// ============================================================
// 轴配置 JSON 持久化 & 板卡同步
// ============================================================

void ConfigMgr::initAxisConfig(stuConfig* cfg, int axisCount, AxisMgr* axisMgr)
{
    m_pAxisCfg = cfg;
    m_axisCount = axisCount;
    m_pAxisMgr = axisMgr;
}

QString ConfigMgr::axisConfigPath() const
{
    return QCoreApplication::applicationDirPath() + QStringLiteral("/axis_config.json");
}

// ---- helper: 单轴 stuConfig → QJsonObject ----
static QJsonObject axisConfigToJson(short axis, const stuConfig& cfg)
{
    int i = axis - 1;

    QJsonObject scalePrf;
    scalePrf[QStringLiteral("alpha")] = static_cast<qint64>(cfg.profileScale[i].alpha);
    scalePrf[QStringLiteral("beta")] = static_cast<qint64>(cfg.profileScale[i].beta);

    QJsonObject scaleEnc;
    scaleEnc[QStringLiteral("alpha")] = static_cast<qint64>(cfg.encScale[i].alpha);
    scaleEnc[QStringLiteral("beta")] = static_cast<qint64>(cfg.encScale[i].beta);

    QJsonObject scaleObj;
    scaleObj[QStringLiteral("profile")] = scalePrf;
    scaleObj[QStringLiteral("encoder")] = scaleEnc;

    QJsonObject dacObj;
    dacObj[QStringLiteral("bias")] = static_cast<int>(cfg.dacBias[i]);
    dacObj[QStringLiteral("limit")] = static_cast<int>(cfg.dacLimit[i]);

    QJsonObject ctrlObj;
    ctrlObj[QStringLiteral("followErrorLimit")] = static_cast<qint64>(cfg.followingErrorLimit[i]);

    QJsonObject prfObj;
    prfObj[QStringLiteral("smoothStopDec")] = cfg.smoothStopDec[i];
    prfObj[QStringLiteral("estopDec")] = cfg.estopDec[i];

    QJsonObject modeObj;
    modeObj[QStringLiteral("controlMode")] = static_cast<int>(cfg.ctrlMode[i]);

    QJsonObject obj;
    obj[QStringLiteral("axis")] = axis;
    obj[QStringLiteral("scale")] = scaleObj;
    obj[QStringLiteral("dac")] = dacObj;
    obj[QStringLiteral("mode")] = modeObj;
    obj[QStringLiteral("control")] = ctrlObj;
    obj[QStringLiteral("profile")] = prfObj;
    return obj;
}

bool ConfigMgr::saveAxisConfig(const QString& filePath) const
{
    if (!m_pAxisCfg) return false;

    QString path = filePath.isEmpty() ? axisConfigPath() : filePath;

    QJsonArray axes;
    for (short axis = 1; axis <= m_axisCount; ++axis)
        axes.append(axisConfigToJson(axis, *m_pAxisCfg));

    QJsonObject root;
    root[QStringLiteral("version")] = 2;
    root[QStringLiteral("axisCount")] = m_axisCount;
    root[QStringLiteral("axes")] = axes;

    QDir().mkpath(QFileInfo(path).absolutePath());

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

bool ConfigMgr::loadAxisConfig(const QString& filePath)
{
    if (!m_pAxisCfg) return false;

    QString path = filePath.isEmpty() ? axisConfigPath() : filePath;

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

    // 先全部置默认值
    for (int i = 0; i < m_axisCount; ++i) {
        m_pAxisCfg->ctrlMode[i] = ControlMode::ClosedLoop;
        m_pAxisCfg->profileScale[i] = stuScaleFactor{ 1, 1 };
        m_pAxisCfg->encScale[i] = stuScaleFactor{ 1, 1 };
        m_pAxisCfg->dacBias[i] = 0;
        m_pAxisCfg->dacLimit[i] = 32767;
        m_pAxisCfg->followingErrorLimit[i] = 32767;
        m_pAxisCfg->smoothStopDec[i] = 100.0;
        m_pAxisCfg->estopDec[i] = 1000.0;
    }

    QJsonArray axes = root.value(QStringLiteral("axes")).toArray();
    for (int n = 0; n < axes.size() && n < m_axisCount; ++n) {
        QJsonObject ax = axes[n].toObject();
        int axis = ax.value(QStringLiteral("axis")).toInt(0);
        if (axis < 1 || axis > m_axisCount)
            continue;
        int i = axis - 1;

        // scale
        QJsonObject scaleObj = ax.value(QStringLiteral("scale")).toObject();
        if (!scaleObj.isEmpty()) {
            QJsonObject prf = scaleObj.value(QStringLiteral("profile")).toObject();
            if (!prf.isEmpty()) {
                m_pAxisCfg->profileScale[i].alpha = static_cast<long>(prf.value(QStringLiteral("alpha")).toDouble(1.0));
                m_pAxisCfg->profileScale[i].beta = static_cast<long>(prf.value(QStringLiteral("beta")).toDouble(1.0));
            }
            QJsonObject enc = scaleObj.value(QStringLiteral("encoder")).toObject();
            if (!enc.isEmpty()) {
                m_pAxisCfg->encScale[i].alpha = static_cast<long>(enc.value(QStringLiteral("alpha")).toDouble(1.0));
                m_pAxisCfg->encScale[i].beta = static_cast<long>(enc.value(QStringLiteral("beta")).toDouble(1.0));
            }
            else {
                m_pAxisCfg->encScale[i] = m_pAxisCfg->profileScale[i];
            }
        }

        // dac
        QJsonObject dacObj = ax.value(QStringLiteral("dac")).toObject();
        if (!dacObj.isEmpty()) {
            m_pAxisCfg->dacBias[i] = static_cast<short>(dacObj.value(QStringLiteral("bias")).toInt(0));
            m_pAxisCfg->dacLimit[i] = static_cast<short>(dacObj.value(QStringLiteral("limit")).toInt(32767));
        }

        // control
        QJsonObject ctrlObj = ax.value(QStringLiteral("control")).toObject();
        if (!ctrlObj.isEmpty()) {
            m_pAxisCfg->followingErrorLimit[i] = static_cast<long>(ctrlObj.value(QStringLiteral("followErrorLimit")).toDouble(32767.0));
        }

        // profile (stop decel)
        QJsonObject prfObj = ax.value(QStringLiteral("profile")).toObject();
        if (!prfObj.isEmpty()) {
            m_pAxisCfg->smoothStopDec[i] = prfObj.value(QStringLiteral("smoothStopDec")).toDouble(100.0);
            m_pAxisCfg->estopDec[i] = prfObj.value(QStringLiteral("estopDec")).toDouble(1000.0);
        }

        // ControlMode
        QJsonObject modeObj = ax.value(QStringLiteral("mode")).toObject();
        if (!modeObj.isEmpty()) {
            int m = modeObj.value(QStringLiteral("controlMode")).toInt(
                static_cast<int>(ControlMode::ClosedLoop));
            if (m >= 0 && m <= 2)
                m_pAxisCfg->ctrlMode[i] = static_cast<ControlMode>(m);
        }
    }

    return true;
}

void ConfigMgr::readAllAxisConfigFromBoard()
{
    if (!m_pAxisCfg || !m_pAxisMgr) return;

    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int i = axis - 1;

        // scale
        m_pAxisMgr->getProfileScale(axis, m_pAxisCfg->profileScale[i].alpha, m_pAxisCfg->profileScale[i].beta);
        short ret = m_pAxisMgr->getEncoderScale(axis, m_pAxisCfg->encScale[i].alpha, m_pAxisCfg->encScale[i].beta);
        if (ret != 0)
            m_pAxisCfg->encScale[i] = m_pAxisCfg->profileScale[i];

        // dac
        m_pAxisCfg->dacBias[i] = m_pAxisMgr->getDacBias(axis);
        m_pAxisCfg->dacLimit[i] = m_pAxisMgr->getDacLimit(axis);

        // follow error
        m_pAxisCfg->followingErrorLimit[i] = m_pAxisMgr->getFollowErrorLimit(axis);

        // stop decel
        double smooth = 100.0, abrupt = 1000.0;
        m_pAxisMgr->getStopDecel(axis, smooth, abrupt);
        m_pAxisCfg->smoothStopDec[i] = smooth;
        m_pAxisCfg->estopDec[i] = abrupt;
    }
}

void ConfigMgr::applyAllAxisConfigToBoard()
{
    if (!m_pAxisCfg || !m_pAxisMgr) return;

    for (short axis = 1; axis <= m_axisCount; ++axis) {
        int i = axis - 1;

        m_pAxisMgr->setProfileScale(axis, m_pAxisCfg->profileScale[i].alpha, m_pAxisCfg->profileScale[i].beta);
        m_pAxisMgr->setEncoderScale(axis, m_pAxisCfg->encScale[i].alpha, m_pAxisCfg->encScale[i].beta);
        m_pAxisMgr->setDacBias(axis, m_pAxisCfg->dacBias[i]);
        m_pAxisMgr->setDacLimit(axis, m_pAxisCfg->dacLimit[i]);
        m_pAxisMgr->setFollowErrorLimit(axis, m_pAxisCfg->followingErrorLimit[i]);
        m_pAxisMgr->setStopDecel(axis, m_pAxisCfg->smoothStopDec[i], m_pAxisCfg->estopDec[i]);

        // 控制模式设置编码器
        switch (m_pAxisCfg->ctrlMode[i]) {
        case ControlMode::ClosedLoop:
            GT_EncOn(axis);
            break;
        case ControlMode::OpenLoop:
        case ControlMode::Simulation:
            GT_EncOff(axis);
            break;
        }
    }
}


// ================================================================
// 1. PID / 控制滤波
// ================================================================
bool ConfigMgr::setPID(short control, short index, const TPid& pid) {
    m_lastError = GtsHal::setPid(control, index, pid);
    if (m_lastError != 0) {
        emit errorOccurred(control, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getPID(short control, short index, TPid& pid) const {
    m_lastError = GtsHal::getPid(control, index, &pid);
    return m_lastError == 0;
}

bool ConfigMgr::setControlFilter(short control, short index) {
    m_lastError = GtsHal::setControlFilter(control, index);
    if (m_lastError != 0) {
        emit errorOccurred(control, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

short ConfigMgr::getControlFilter(short control) const {
    short index = 0;
    GtsHal::getControlFilter(control, &index);
    return index;
}

bool ConfigMgr::setKvffFilter(short control, short index, short kvffFilterExp, double accMax) {
    m_lastError = GtsHal::setKvffFilter(control, index, kvffFilterExp, accMax);
    if (m_lastError != 0) {
        emit errorOccurred(control, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getKvffFilter(short control, short index, short& kvffFilterExp, double& accMax) const {
    m_lastError = GtsHal::getKvffFilter(control, index, &kvffFilterExp, &accMax);
    return m_lastError == 0;
}

bool ConfigMgr::setAxisBand(short axis, long band, long time) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setAxisBand(axis, band, time);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getAxisBand(short axis, long& band, long& time) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getAxisBand(axis, &band, &time);
    return m_lastError == 0;
}

bool ConfigMgr::setControlConfigEx(short control, const TControlConfigEx& cfg) {
    m_lastError = GtsHal::setControlConfigEx(control, cfg);
    if (m_lastError != 0) {
        emit errorOccurred(control, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getControlConfigEx(short control, TControlConfigEx& cfg) const {
    m_lastError = GtsHal::getControlConfigEx(control, &cfg);
    return m_lastError == 0;
}

bool ConfigMgr::setControlSuperimposed(short control, short superimposedType, short superimposedIndex) {
    m_lastError = GtsHal::setControlSuperimposed(control, superimposedType, superimposedIndex);
    if (m_lastError != 0) {
        emit errorOccurred(control, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getControlSuperimposed(short control, short& type, short& index) const {
    m_lastError = GtsHal::getControlSuperimposed(control, &type, &index);
    return m_lastError == 0;
}

// ================================================================
// 2. 背隙补偿
// ================================================================
bool ConfigMgr::setBacklash(short axis, long compValue, double compChangeValue, long compDir) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setBacklash(axis, compValue, compChangeValue, compDir);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getBacklash(short axis, long& compValue, double& compChangeValue, long& compDir) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getBacklash(axis, &compValue, &compChangeValue, &compDir);
    return m_lastError == 0;
}

// ================================================================
// 3. 丝杠补偿 / 2D 补偿
// ================================================================
bool ConfigMgr::setLeadScrewComp(short axis, short n, long startPos, long lenPos,
    long* pCompPos, long* pCompNeg) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setLeadScrewComp(axis, n, startPos, lenPos, pCompPos, pCompNeg);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::enableLeadScrewComp(short axis, short mode) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::enableLeadScrewComp(axis, mode);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getLeadScrewCompValue(short axis, short dir, long pos, long& compValue) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getLeadScrewCompInnerValue(axis, dir, pos, &compValue);
    return m_lastError == 0;
}

bool ConfigMgr::setLeadScrewCrossComp(short axis, short n, long startPos, long lenPos,
    long* pCompPos, long* pCompNeg, short link) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setLeadScrewCrossComp(axis, n, startPos, lenPos, pCompPos, pCompNeg, link);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::enableLeadScrewCrossComp(short axis, short mode) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::enableLeadScrewCrossComp(axis, mode);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setLeadScrewLink(short axis, short link) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setLeadScrewLink(axis, link);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

short ConfigMgr::getLeadScrewLink(short axis) const {
    if (!isValidAxis(axis)) return -1;
    short link = 0;
    GtsHal::getLeadScrewLink(axis, &link);
    return link;
}

bool ConfigMgr::setCompensate2DTable(short idx, const TCompensate2DTable& tbl,
    long* pData, short externComp) {
    m_lastError = GtsHal::setCompensate2DTable(idx, tbl, pData, externComp);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getCompensate2DTable(short idx, TCompensate2DTable& tbl) const {
    m_lastError = GtsHal::getCompensate2DTable(idx, &tbl);
    return m_lastError == 0;
}

bool ConfigMgr::setCompensate2D(short axis, const TCompensate2D& comp) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setCompensate2D(axis, comp);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getCompensate2D(short axis, TCompensate2D& comp) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getCompensate2D(axis, &comp);
    return m_lastError == 0;
}

double ConfigMgr::getCompensate2DValue(short axis) const {
    if (!isValidAxis(axis)) return 0.0;
    double val = 0.0;
    GtsHal::getCompensate2DValue(axis, &val);
    return val;
}

bool ConfigMgr::getCompensate(short axis, double& pitchError, double& crossError,
    double& backlashError, double& encPos, double& prfPos) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getCompensate(axis, &pitchError, &crossError,
        &backlashError, &encPos, &prfPos);
    return m_lastError == 0;
}

// ================================================================
// 4. 位置比较 (1D)
// ================================================================
bool ConfigMgr::setComparePort(short channel, short hsio0, short hsio1) {
    m_lastError = GtsHal::setComparePort(channel, hsio0, hsio1);
    if (m_lastError != 0) {
        emit errorOccurred(channel, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::comparePulse(short level, short outputType, short time) {
    m_lastError = GtsHal::comparePulse(level, outputType, time);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compareStop() {
    m_lastError = GtsHal::compareStop();
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compareStatus(short& status, long& count) const {
    m_lastError = GtsHal::compareStatus(&status, &count);
    return m_lastError == 0;
}

bool ConfigMgr::compareData(short encoder, short source, short pulseType, short startLevel,
    short time, long* pBuf1, short count1, long* pBuf2, short count2) {
    m_lastError = GtsHal::compareData(encoder, source, pulseType, startLevel, time,
        pBuf1, count1, pBuf2, count2);
    if (m_lastError != 0) {
        emit errorOccurred(encoder, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compareLinear(short encoder, short channel, long startPos, long repeatTimes,
    long interval, short time, short source) {
    m_lastError = GtsHal::compareLinear(encoder, channel, startPos, repeatTimes,
        interval, time, source);
    if (m_lastError != 0) {
        emit errorOccurred(encoder, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compareContinuePulseMode(short mode, short count, short standTime) {
    m_lastError = GtsHal::compareContinuePulseMode(mode, count, standTime);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 5. 2D 位置比较
// ================================================================
bool ConfigMgr::compare2DSetMode(short chn, short mode) {
    m_lastError = GtsHal::compare2DMode(chn, mode);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DPulse(short chn, short level, short outputType, short time) {
    m_lastError = GtsHal::compare2DPulse(chn, level, outputType, time);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DStop(short chn) {
    m_lastError = GtsHal::compare2DStop(chn);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DClear(short chn) {
    m_lastError = GtsHal::compare2DClear(chn);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DStatus(short chn, short& status, long& count,
    short& fifo, short& fifoCount) const {
    m_lastError = GtsHal::compare2DStatus(chn, &status, &count, &fifo, &fifoCount);
    return m_lastError == 0;
}

bool ConfigMgr::compare2DSetParams(short chn, const T2DComparePrm& prm) {
    m_lastError = GtsHal::compare2DSetPrm(chn, prm);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DData(short chn, short count, const T2DCompareData* pBuf, short fifo) {
    m_lastError = GtsHal::compare2DData(chn, count, pBuf, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DStart(short chn) {
    m_lastError = GtsHal::compare2DStart(chn);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DClearData(short chn) {
    m_lastError = GtsHal::compare2DClearData(chn);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::compare2DSetPreOutTime(short chn, double preOutputTime) {
    m_lastError = GtsHal::compare2DSetPreOutTime(chn, preOutputTime);
    if (m_lastError != 0) {
        emit errorOccurred(chn, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 6. PosCompare (新版)
// ================================================================
bool ConfigMgr::setPosCompareMode(short index, const TPosCompareMode& mode) {
    m_lastError = GtsHal::setPosCompareMode(index, mode);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getPosCompareMode(short index, TPosCompareMode& mode) const {
    m_lastError = GtsHal::getPosCompareMode(index, &mode);
    return m_lastError == 0;
}

bool ConfigMgr::posCompareStart(short index) {
    m_lastError = GtsHal::posCompareStart(index);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::posCompareStop(short index) {
    m_lastError = GtsHal::posCompareStop(index);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::posCompareClear(short index) {
    m_lastError = GtsHal::posCompareClear(index);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::posCompareStatus(short index, TPosCompareStatus& status) const {
    m_lastError = GtsHal::posCompareStatus(index, &status);
    return m_lastError == 0;
}

bool ConfigMgr::posCompareData(short index, const TPosCompareData& data) {
    m_lastError = GtsHal::posCompareData(index, data);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::posCompareSetLinear(short index, const TPosCompareLinear& linear) {
    m_lastError = GtsHal::posCompareSetLinear(index, linear);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::posCompareSetPsoParams(short index, const TPosComparePsoPrm& prm) {
    m_lastError = GtsHal::posCompareSetPsoPrm(index, prm);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::posCompareSetContinueMode(short index, const TPosCompareContinueMode& mode) {
    m_lastError = GtsHal::posCompareSetContinueMode(index, mode);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 7. 龙门 (Gantry)
// ================================================================
bool ConfigMgr::enableGantry(short master, short slave, double masterKp, double slaveKp) {
    m_lastError = GtsHal::enableGantry(master, slave, masterKp, slaveKp);
    if (m_lastError != 0) {
        emit errorOccurred(master, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::disableGantry() {
    m_lastError = GtsHal::disableGantry();
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setGantryErrorLimit(long errLmt) {
    m_lastError = GtsHal::setGantryErrLmt(errLmt);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

long ConfigMgr::getGantryErrorLimit() const {
    long limit = 0;
    GtsHal::getGantryErrLmt(&limit);
    return limit;
}

bool ConfigMgr::zeroGantryPos(short master, short slave) {
    m_lastError = GtsHal::zeroGantryPos(master, slave);
    if (m_lastError != 0) {
        emit errorOccurred(master, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setGantryMode(short group, short master, short slave,
    short mode, long syncErrorLimit) {
    m_lastError = GtsHal::setGantryMode(group, master, slave, mode, syncErrorLimit);
    if (m_lastError != 0) {
        emit errorOccurred(group, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getGantryMode(short group, short& master, short& slave,
    short& mode, long& syncErrorLimit) const {
    m_lastError = GtsHal::getGantryMode(group, &master, &slave, &mode, &syncErrorLimit);
    return m_lastError == 0;
}

bool ConfigMgr::setGantryPID(short group, const TPid& gantryPid, const TPid& yawPid) {
    m_lastError = GtsHal::setGantryPid(group, gantryPid, yawPid);
    if (m_lastError != 0) {
        emit errorOccurred(group, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getGantryPID(short group, TPid& gantryPid, TPid& yawPid) const {
    m_lastError = GtsHal::getGantryPid(group, &gantryPid, &yawPid);
    return m_lastError == 0;
}

bool ConfigMgr::gantryAxisOn(short group) {
    m_lastError = GtsHal::gantryAxisOn(group);
    if (m_lastError != 0) {
        emit errorOccurred(group, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::gantryAxisOff(short group) {
    m_lastError = GtsHal::gantryAxisOff(group);
    if (m_lastError != 0) {
        emit errorOccurred(group, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 8. 手轮 (Handwheel)
// ================================================================
bool ConfigMgr::handwheelInit() {
    m_lastError = GtsHal::handwheelInit();
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setHandwheelStopDecel(short slave, double decSmooth, double decAbrupt) {
    m_lastError = GtsHal::setHandwheelStopDec(slave, decSmooth, decAbrupt);
    if (m_lastError != 0) {
        emit errorOccurred(slave, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::startHandwheel(short slave, short master, short masterEven, short slaveEven,
    short intervalTime, double acc, double dec, double vel,
    short stopWaitTime) {
    m_lastError = GtsHal::startHandwheel(slave, master, masterEven, slaveEven,
        intervalTime, acc, dec, vel, stopWaitTime);
    if (m_lastError != 0) {
        emit errorOccurred(slave, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::endHandwheel(short slave) {
    m_lastError = GtsHal::endHandwheel(slave);
    if (m_lastError != 0) {
        emit errorOccurred(slave, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 9. 触发 (Trigger)
// ================================================================
bool ConfigMgr::setTrigger(short i, const TTrigger& trigger) {
    m_lastError = GtsHal::setTrigger(i, trigger);
    if (m_lastError != 0) {
        emit errorOccurred(i, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getTrigger(short i, TTrigger& trigger) const {
    m_lastError = GtsHal::getTrigger(i, &trigger);
    return m_lastError == 0;
}

bool ConfigMgr::getTriggerStatus(short i, TTriggerStatus& status) const {
    m_lastError = GtsHal::getTriggerStatus(i, &status);
    return m_lastError == 0;
}

bool ConfigMgr::getTriggerStatusEx(short i, TTriggerStatusEx& statusEx) const {
    m_lastError = GtsHal::getTriggerStatusEx(i, &statusEx);
    return m_lastError == 0;
}

bool ConfigMgr::clearTriggerStatus(short i) {
    m_lastError = GtsHal::clearTriggerStatus(i);
    if (m_lastError != 0) {
        emit errorOccurred(i, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getTriggerLatchValue(short i, long count, long* pValue,
    long* pCount, TLatchValueInfo* pInfo) const {
    m_lastError = GtsHal::getTriggerLatchValue(i, count, pValue, pCount, pInfo);
    return m_lastError == 0;
}

// ================================================================
// 10. 坐标变换
// ================================================================
bool ConfigMgr::setTransformOrthogonal(short index, const TTransformOrthogonal& data) {
    m_lastError = GtsHal::setTransformOrthogonal(index, data);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getTransformOrthogonal(short index, TTransformOrthogonal& data) const {
    m_lastError = GtsHal::getTransformOrthogonal(index, &data);
    return m_lastError == 0;
}

bool ConfigMgr::getTransformOrthogonalPosition(short index, double& x, double& y) const {
    m_lastError = GtsHal::getTransformOrthogonalPosition(index, &x, &y);
    return m_lastError == 0;
}

bool ConfigMgr::setTransformPerpendicularity(short index, const TTransformPerpendicularity& data) {
    m_lastError = GtsHal::setTransformPerpendicularity(index, data);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getTransformPerpendicularity(short index, TTransformPerpendicularity& data) const {
    m_lastError = GtsHal::getTransformPerpendicularity(index, &data);
    return m_lastError == 0;
}

bool ConfigMgr::getTransformPerpendicularityPosition(short index, double& x, double& y, double& z) const {
    m_lastError = GtsHal::getTransformPerpendicularityPosition(index, &x, &y, &z);
    return m_lastError == 0;
}

// ================================================================
// 11. Smart Cutter
// ================================================================
bool ConfigMgr::setSmartCutterParams(short index, const TSmartCutterPrm& prm) {
    m_lastError = GtsHal::setSmartCutterPrm(index, prm);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getSmartCutterParams(short index, TSmartCutterPrm& prm) const {
    m_lastError = GtsHal::getSmartCutterPrm(index, &prm);
    return m_lastError == 0;
}

bool ConfigMgr::smartCutterOn(short index) {
    m_lastError = GtsHal::smartCutterOn(index);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::smartCutterOff(short index) {
    m_lastError = GtsHal::smartCutterOff(index);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getSmartCutterInfo(short index, TSmartCutterInfo& info) const {
    m_lastError = GtsHal::getSmartCutterInfo(index, &info);
    return m_lastError == 0;
}

bool ConfigMgr::setSmartCutterValue(short index, double radiusValue, double angleValue) {
    m_lastError = GtsHal::setSmartCutterValue(index, radiusValue, angleValue);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::smartCutterStart(short index) {
    m_lastError = GtsHal::smartCutterStart(index);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 12. 自动对焦
// ================================================================
bool ConfigMgr::autoFocus(unsigned short mode, double kp, short reverse, short channel) {
    m_lastError = GtsHal::autoFocus(mode, kp, reverse, channel);
    if (m_lastError != 0) {
        emit errorOccurred(channel, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setAutoFocusRefVol(double refVol, double maxVol, double minVol, short channel) {
    m_lastError = GtsHal::setAutoFocusRefVol(refVol, maxVol, minVol, channel);
    if (m_lastError != 0) {
        emit errorOccurred(channel, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getAutoFocusStatus(unsigned short& status) const {
    m_lastError = GtsHal::getAutoFocusStatus(&status, 1);
    return m_lastError == 0;
}

bool ConfigMgr::configAutoFocus(short chnAdc, short channel) {
    m_lastError = GtsHal::configAutoFocus(chnAdc, channel);
    if (m_lastError != 0) {
        emit errorOccurred(channel, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setAutoFocusAuxParams(double kf, double kd, double limitKd, short channel) {
    m_lastError = GtsHal::setAutoFocusAuxPrm(kf, kd, limitKd, channel);
    if (m_lastError != 0) {
        emit errorOccurred(channel, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setAutoFocusDeadVoltage(double voltage, short channel) {
    m_lastError = GtsHal::setAutoFocusDeadVoltage(voltage, channel);
    if (m_lastError != 0) {
        emit errorOccurred(channel, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 13. 信号检测 / 滤波
// ================================================================
bool ConfigMgr::setSignalTimeFilter(short type, short index, double filterWidth) {
    m_lastError = GtsHal::setSignalTimeFilter(type, index, filterWidth);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

double ConfigMgr::getSignalTimeFilter(short type, short index) const {
    double width = 0.0;
    GtsHal::getSignalTimeFilter(type, index, &width);
    return width;
}

bool ConfigMgr::clearSignalDetect(short index) {
    m_lastError = GtsHal::clearSignalDetect(index);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setSignalDetect(short index, short enable, const TSignalDetect& prm) {
    m_lastError = GtsHal::setSignalDetect(index, enable, prm);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getSignalDetect(short index, short& enable, TSignalDetect& prm) const {
    m_lastError = GtsHal::getSignalDetect(index, &enable, &prm);
    return m_lastError == 0;
}

bool ConfigMgr::getSignalDetectStatus(short index, TSignalDetectStatus& status) const {
    m_lastError = GtsHal::getSignalDetectStatus(index, &status);
    return m_lastError == 0;
}

// ================================================================
// 14. 变量
// ================================================================
bool ConfigMgr::setLongVar(short index, long value) {
    m_lastError = GtsHal::setLongVar(index, value);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

long ConfigMgr::getLongVar(short index) const {
    long value = 0;
    GtsHal::getLongVar(index, &value);
    return value;
}

bool ConfigMgr::setDoubleVar(short index, double value) {
    m_lastError = GtsHal::setDoubleVar(index, value);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

double ConfigMgr::getDoubleVar(short index) const {
    double value = 0.0;
    GtsHal::getDoubleVar(index, &value);
    return value;
}

bool ConfigMgr::setFlagVar(short index, short mode, short value) {
    m_lastError = GtsHal::setFlagVar(index, mode, value);
    if (m_lastError != 0) {
        emit errorOccurred(index, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getFlagVar(short index, short& mode, short& value) const {
    m_lastError = GtsHal::getFlagVar(index, &mode, &value);
    return m_lastError == 0;
}

// ================================================================
// 15. 脚本
// ================================================================
bool ConfigMgr::compile(const QString& fileName, TCompileInfo& wrongInfo) {
    m_lastError = GtsHal::compile(fileName.toLocal8Bit().constData(), &wrongInfo);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::download(const QString& fileName) {
    m_lastError = GtsHal::download(fileName.toLocal8Bit().constData());
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getFunctionId(const QString& funName, short& funId) {
    m_lastError = GtsHal::getFunId(funName.toLocal8Bit().constData(), &funId);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::bind(short thread, short funId, short page) {
    m_lastError = GtsHal::bind(thread, funId, page);
    if (m_lastError != 0) {
        emit errorOccurred(thread, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::runThread(short thread) {
    m_lastError = GtsHal::runThread(thread);
    if (m_lastError != 0) {
        emit errorOccurred(thread, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::stopThread(short thread) {
    m_lastError = GtsHal::stopThread(thread);
    if (m_lastError != 0) {
        emit errorOccurred(thread, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::pauseThread(short thread) {
    m_lastError = GtsHal::pauseThread(thread);
    if (m_lastError != 0) {
        emit errorOccurred(thread, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getThreadStatus(short thread, TThreadSts& sts) const {
    m_lastError = GtsHal::getThreadSts(thread, &sts);
    return m_lastError == 0;
}

bool ConfigMgr::getVarId(const QString& funName, const QString& varName, TVarInfo& varInfo) const {
    m_lastError = GtsHal::getVarId(funName.toLocal8Bit().constData(),
        varName.toLocal8Bit().constData(), &varInfo);
    return m_lastError == 0;
}

bool ConfigMgr::setVarValue(short page, const TVarInfo& varInfo, double* pValue, short count) {
    m_lastError = GtsHal::setVarValue(page, varInfo, pValue, count);
    if (m_lastError != 0) {
        emit errorOccurred(page, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getVarValue(short page, const TVarInfo& varInfo, double* pValue, short count) const {
    m_lastError = GtsHal::getVarValue(page, varInfo, pValue, count);
    return m_lastError == 0;
}

// ================================================================
// 16. 摇杆
// ================================================================
bool ConfigMgr::setJoystickMapAxis(short idx, short* axis) {
    m_lastError = GtsHal::setJoystickMapAxis(idx, axis);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getJoystickMapAxis(short idx, short* pAxis) const {
    m_lastError = GtsHal::getJoystickMapAxis(idx, pAxis);
    return m_lastError == 0;
}

bool ConfigMgr::joystickEnable(short idx, short enable) {
    m_lastError = GtsHal::joystickEnable(idx, enable);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setJoystickSerialPortParams(short idx, const TSericalPortPrm& prm) {
    m_lastError = GtsHal::setJoystickSericalPortPrm(idx, prm);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getJoystickSerialPortParams(short idx, TSericalPortPrm& prm) const {
    m_lastError = GtsHal::getJoystickSericalPortPrm(idx, &prm);
    return m_lastError == 0;
}

bool ConfigMgr::joystickCheckEnable(short idx, short checkEnable) {
    m_lastError = GtsHal::joystickCheckEnable(idx, checkEnable);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

long ConfigMgr::getJoystickStatus(short idx) const {
    long sts = 0;
    GtsHal::getJoystickSts(idx, &sts);
    return sts;
}

long ConfigMgr::getJoystickValue(short idx) const {
    long val = 0;
    GtsHal::getJoystickValue(idx, &val);
    return val;
}

bool ConfigMgr::setJoystickMotionParams(short idx, const TJoystickMoitonPrm& prm) {
    m_lastError = GtsHal::setJoystickMotionPrm(idx, prm);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getJoystickMotionParams(short idx, TJoystickMoitonPrm& prm) const {
    m_lastError = GtsHal::getJoystickMotionPrm(idx, &prm);
    return m_lastError == 0;
}

bool ConfigMgr::setJoystickMotionVel(short idx, const TJoystickMoitonVel& vel) {
    m_lastError = GtsHal::setJoystickMotionVel(idx, vel);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getJoystickMotionVel(short idx, TJoystickMoitonVel& vel) const {
    m_lastError = GtsHal::getJoystickMotionVel(idx, &vel);
    return m_lastError == 0;
}

bool ConfigMgr::joystickReset(short idx) {
    m_lastError = GtsHal::joystickReset(idx);
    if (m_lastError != 0) {
        emit errorOccurred(idx, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

// ================================================================
// 17. 轴叠加 / 输入整形 / 运动平滑
// ================================================================
bool ConfigMgr::setMotionSmooth(short axis, const TMotionSmooth& smooth) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setMotionSmooth(axis, smooth);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getMotionSmooth(short axis, TMotionSmooth& smooth) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getMotionSmooth(axis, &smooth);
    return m_lastError == 0;
}

bool ConfigMgr::setAxisAddition(short axis, short dataType, short additionIndex, short additionType) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setAxisAddition(axis, dataType, additionIndex, additionType);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getAxisAddition(short axis, short dataType, short& additionIndex, short& additionType) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getAxisAddition(axis, dataType, &additionIndex, &additionType);
    return m_lastError == 0;
}

bool ConfigMgr::setAxisInputShaping(short axis, short enable, short count, double k) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setAxisInputShaping(axis, enable, count, k);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::setMcOverride(short axis, short mode, double override, double smoothTime) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setMcOverride(axis, mode, override, smoothTime);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getMcOverride(short axis, short mode, double& overrideTarget,
    double& smoothTime, double& overrideVal) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getMcOverride(axis, mode, &overrideTarget, &smoothTime, &overrideVal);
    return m_lastError == 0;
}

// ================================================================
// 18. 步进模式 / 输出电平
// ================================================================
bool ConfigMgr::setStepOutLevel(short axis, short type, short reverse) {
    if (!isValidAxis(axis)) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1").arg(axis));
        return false;
    }
    m_lastError = GtsHal::setStepOutLevel(axis, type, reverse);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getStepOutLevel(short axis, short type, short& reverse) const {
    if (!isValidAxis(axis)) return false;
    m_lastError = GtsHal::getStepOutLevel(axis, type, &reverse);
    return m_lastError == 0;
}

bool ConfigMgr::stepDir(short step) {
    m_lastError = GtsHal::stepDir(step);
    if (m_lastError != 0) {
        emit errorOccurred(step, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::stepPulse(short step) {
    m_lastError = GtsHal::stepPulse(step);
    if (m_lastError != 0) {
        emit errorOccurred(step, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::stepOrthogonal(short step) {
    m_lastError = GtsHal::stepOrthogonal(step);
    if (m_lastError != 0) {
        emit errorOccurred(step, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool ConfigMgr::getMachineWorkPos(short crd, short mode, double& machinePos, double& workPos) const {
    m_lastError = GtsHal::getMachineWorkPos(crd, mode, &machinePos, &workPos);
    return m_lastError == 0;
}

bool ConfigMgr::checkCrdLineTime(short crd, double x, double y, double z,
    double& velMax, double& acc, double& velEnd,
    double& time, long& errorCode) const {
    m_lastError = GtsHal::checkCrdLineTime(crd, x, y, z, &velMax, &acc, &velEnd, &time, &errorCode);
    return m_lastError == 0;
}

// ================================================================
// 19. 便利方法
// ================================================================
QString ConfigMgr::lastErrorString() const {
    return GtsErrorToString(m_lastError);
}
