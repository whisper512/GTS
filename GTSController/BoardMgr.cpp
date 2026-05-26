#include "TotalMgr.h"
#include "BoardMgr.h"

BoardMgr::BoardMgr(QObject* parent)
    : QObject(parent)
{
}

BoardMgr::~BoardMgr() {
    if (m_isOpen) {
        close();
    }
}

bool BoardMgr::open(short channel, short param)
{
    if (m_isOpen) {
        // 如果已经打开，先关闭再重新打开
        GtsHal::close();
        m_isOpen = false;
    }

    m_lastError = GtsHal::open(channel, param);
    if (m_lastError == 0) {
        m_isOpen = true;
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("打开gts400板卡成功"),Qt::darkGreen);
        }
        return true;
    }
    else {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("打开gts400板卡失败"), Qt::darkRed);
        }
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
}

bool BoardMgr::close()
{
    if (!m_isOpen) return true;

    m_lastError = GtsHal::close();
    m_isOpen = false;
    if (m_lastError == 0) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("关闭gts400板卡成功"), Qt::darkGreen);
        }
        return true;
    }
    else {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("关闭gts400板卡失败"), Qt::darkRed);
        }
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
}

bool BoardMgr::reset() {
    m_lastError = GtsHal::reset();
    if (m_lastError == 0) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("重置gts400板卡成功"), Qt::darkGreen);
        }
        m_isOpen = false; 
        return true;
    }
    else {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("重置gts400板卡失败"), Qt::darkRed);
        }
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
}

bool BoardMgr::setCardNo(short index) {
    m_lastError = GtsHal::setCardNo(index);
    if (m_lastError == 0) {
        m_cardNo = index;
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("设置卡号为：%1").arg(index), Qt::darkGreen);
        }
        return true;
    }
    else {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
}

short BoardMgr::getCardNo() {
    short index = 0;
    GtsHal::getCardNo(&index);
    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("当前卡号：%1").arg(index), Qt::darkGreen);
    }
    return index;
}

bool BoardMgr::loadConfig(const QString& filePath) {
    m_lastError = GtsHal::loadConfig(filePath.toLocal8Bit().constData());
    if (m_lastError != 0) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("加载配置文件失败：%1").arg(filePath), Qt::darkRed);
        }
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }

    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("加载配置文件成功：%1").arg(filePath), Qt::darkGreen);
    }
    return true;
}

bool BoardMgr::saveConfig(const QString& filePath) {
    m_lastError = GtsHal::saveConfigToFile(filePath.toLocal8Bit().constData());
    if (m_lastError != 0) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("保存配置文件失败：%1").arg(filePath), Qt::darkRed);
        }
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("保存配置文件成功：%1").arg(filePath), Qt::darkGreen);
    }
    return true;
}

bool BoardMgr::uploadConfig() {
    m_lastError = GtsHal::uploadConfig();
    if (m_lastError != 0) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("上传配置文件失败"), Qt::darkRed);
        }
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("上传配置文件成功"), Qt::darkGreen);
    }
    return true;
}

bool BoardMgr::downloadConfig() {
    m_lastError = GtsHal::downloadConfig();
    if (m_lastError != 0) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("下载配置文件失败"), Qt::darkRed);
        }
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("下载配置文件成功"), Qt::darkGreen);
    }
    return true;
}

QString BoardMgr::dllVersion() const {
    char* pVer = nullptr;
    short ret = GtsHal::getDllVersion(&pVer);
    if (ret == 0 && pVer) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("gts400板卡版本：%1").arg(QString::fromLocal8Bit(pVer)), Qt::darkGreen);
        }
        return QString::fromLocal8Bit(pVer);
    }
    return QString();
}

QString BoardMgr::firmwareVersion() const {
    char* pVer = nullptr;
    short ret = GtsHal::getVersion(&pVer);
    if (ret == 0 && pVer) {
        if (m_pTotalMgr)
        {
            emit m_pTotalMgr->sendLog(QStringLiteral("固件版本：%1").arg(QString::fromLocal8Bit(pVer)), Qt::darkGreen);
        }
        return QString::fromLocal8Bit(pVer);
    }
    return QString();
}

CardInfo BoardMgr::cardInfo() const {
    CardInfo info = { -1, -1 };
    GtsHal::getCardInfo(&info.cardNum, &info.cardType);
    return info;
}

DriverVersion BoardMgr::driverVersion() const {
    DriverVersion dv = { 0, 0 };
    GtsHal::getDriverVersion(&dv.mainVer, &dv.slaveVer);
    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("驱动版本：%1.%2").arg(dv.mainVer).arg(dv.slaveVer), Qt::darkGreen);
    }
    return dv;
}

short BoardMgr::interfaceBoardStatus() const {
    short sts = 0;
    GtsHal::getInterfaceBoardSts(&sts);
    return sts;
}

bool BoardMgr::setInterfaceBoardStatus(short type) {
    m_lastError = GtsHal::setInterfaceBoardSts(type);
    if (m_lastError != 0) {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    return true;
}

unsigned long BoardMgr::clock() const {
    unsigned long clk = 0;
    GtsHal::getClock(&clk, nullptr);
    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("时钟：%1").arg(clk), Qt::darkGreen);
    }
    return clk;
}

unsigned long BoardMgr::clockHighPrecision() const {
    unsigned long clk = 0;
    GtsHal::getClockHighPrecision(&clk);
    if (m_pTotalMgr)
    {
        emit m_pTotalMgr->sendLog(QStringLiteral("高精度时钟：%1").arg(clk), Qt::darkGreen);
    }
    return clk;
}

bool BoardMgr::delay(unsigned short milliseconds) {
    m_lastError = GtsHal::delay(milliseconds);
    return m_lastError == 0;
}

bool BoardMgr::delayHighPrecision(unsigned short microseconds) {
    m_lastError = GtsHal::delayHighPrecision(microseconds);
    return m_lastError == 0;
}

bool BoardMgr::interruptOn(TInterruptCallback pCallback) {
    m_lastError = GtsHal::interruptOn(pCallback);
    if (m_lastError != 0) {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    return true;
}

bool BoardMgr::interruptOff() {
    m_lastError = GtsHal::interruptOff();
    return m_lastError == 0;
}

bool BoardMgr::setInterruptMask(long mask) {
    m_lastError = GtsHal::setInterruptMask(mask);
    return m_lastError == 0;
}

long BoardMgr::interruptMask() const {
    long mask = 0;
    GtsHal::getInterruptMask(&mask);
    return mask;
}

bool BoardMgr::triggerInterrupt(short param) {
    m_lastError = GtsHal::interruptTrigger(param);
    return m_lastError == 0;
}

QString BoardMgr::uuid() const {
    char code[64] = { 0 };
    short ret = GtsHal::getUuid(code, 64);
    if (ret == 0) {
        return QString::fromLocal8Bit(code);
    }
    return QString();
}

bool BoardMgr::setUuid(const QString& code) {
    QByteArray ba = code.toLocal8Bit();
    m_lastError = GtsHal::setUuid(ba.data(), static_cast<short>(ba.size()));
    if (m_lastError != 0) {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    return true;
}

short BoardMgr::displayDip() const {
    short mode = 0;
    GtsHal::getDisplayDip(&mode);
    return mode;
}

bool BoardMgr::setDisplayDip(short mode) {
    m_lastError = GtsHal::setDisplayDip(mode);
    return m_lastError == 0;
}

bool BoardMgr::setDeviceShareMax(short count) {
    m_lastError = GtsHal::setDeviceShareMax(count);
    return m_lastError == 0;
}

QString BoardMgr::lastErrorString() const {
    return GtsErrorToString(m_lastError);
}
