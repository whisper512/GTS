#include "BoardMgr.h"

// ============================================================
// 构造/析构
// ============================================================
BoardMgr::BoardMgr(QObject* parent)
    : QObject(parent)
{
}

BoardMgr::~BoardMgr() {
    if (m_isOpen) {
        close();
    }
}

// ============================================================
// 1. 板卡生命周期
// ============================================================
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
        emit opened();
        return true;
    }
    else {
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
        emit closed();
        return true;
    }
    else {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
}

bool BoardMgr::reset() {
    m_lastError = GtsHal::reset();
    if (m_lastError == 0) {
        m_isOpen = false;  // 复位后需要重新 open
        return true;
    }
    else {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
}

// ============================================================
// 2. 板卡选择
// ============================================================
bool BoardMgr::setCardNo(short index) {
    m_lastError = GtsHal::setCardNo(index);
    if (m_lastError == 0) {
        m_cardNo = index;
        return true;
    }
    else {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
}

short BoardMgr::cardNo() {
    short index = 0;
    GtsHal::getCardNo(&index);
    return index;
}

// ============================================================
// 3. 配置加载/保存
// ============================================================
bool BoardMgr::loadConfig(const QString& filePath) {
    m_lastError = GtsHal::loadConfig(filePath.toLocal8Bit().constData());
    if (m_lastError != 0) {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    return true;
}

bool BoardMgr::saveConfig(const QString& filePath) {
    m_lastError = GtsHal::saveConfigToFile(filePath.toLocal8Bit().constData());
    if (m_lastError != 0) {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    return true;
}

bool BoardMgr::uploadConfig() {
    m_lastError = GtsHal::uploadConfig();
    if (m_lastError != 0) {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    return true;
}

bool BoardMgr::downloadConfig() {
    m_lastError = GtsHal::downloadConfig();
    if (m_lastError != 0) {
        emit errorOccurred(m_lastError, GtsErrorToString(m_lastError));
        return false;
    }
    return true;
}

// ============================================================
// 4. 版本/信息查询
// ============================================================
QString BoardMgr::dllVersion() const {
    char* pVer = nullptr;
    short ret = GtsHal::getDllVersion(&pVer);
    if (ret == 0 && pVer) {
        return QString::fromLocal8Bit(pVer);
    }
    return QString();
}

QString BoardMgr::firmwareVersion() const {
    char* pVer = nullptr;
    short ret = GtsHal::getVersion(&pVer);
    if (ret == 0 && pVer) {
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

// ============================================================
// 5. 时钟与延时
// ============================================================
unsigned long BoardMgr::clock() const {
    unsigned long clk = 0;
    GtsHal::getClock(&clk, nullptr);
    return clk;
}

unsigned long BoardMgr::clockHighPrecision() const {
    unsigned long clk = 0;
    GtsHal::getClockHighPrecision(&clk);
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

// ============================================================
// 6. 中断控制
// ============================================================
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

// ============================================================
// 7. UUID
// ============================================================
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

// ============================================================
// 8. 杂项
// ============================================================
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
