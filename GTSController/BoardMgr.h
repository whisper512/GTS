#ifndef BOARDMGR_H
#define BOARDMGR_H

#include <QObject>
#include <QString>

#include "GtsHal.h"

struct CardInfo {
    short cardNum;
    short cardType;
};

struct DriverVersion {
    unsigned short mainVer;
    unsigned short slaveVer;
};

// ============================================================
// BoardMgr — GTS 板卡管理器
// 职责;开/关/复位卡/配置加载/保存/版本信息/时钟/中断
// ============================================================

class BoardMgr : public QObject {
    Q_OBJECT
public:
    explicit BoardMgr(QObject* parent = nullptr);
    ~BoardMgr();


    // 打开板卡
    // @param channel  板卡通道号 (0=PCI/PCIe 插槽索引)
    // @param param    保留参数,默认 1
    bool open(short channel = 0, short param = 1);
    // 关闭板卡
    bool close();
    // 复位板卡软复位
    bool reset();
    // 是否已打开
    bool isOpen() const { return m_isOpen; }


    // 设置当前操作的板卡编号
    bool setCardNo(short index);
    /// 获取当前板卡编号
    short cardNo();


    // 从文件加载配置
    bool loadConfig(const QString& filePath);
    // 保存当前配置到文件
    bool saveConfig(const QString& filePath);
    // 从板卡上传配置到主机内存
    bool uploadConfig();
    // 将主机内存配置下载到板卡
    bool downloadConfig();


    // 获取 DLL 版本号字符串
    QString dllVersion() const;
    // 获取固件版本号字符串
    QString firmwareVersion() const;
    // 获取板卡信息（卡编号、卡类型）
    CardInfo cardInfo() const;
    // 获取驱动版本
    DriverVersion driverVersion() const;
    // 获取接口板状态
    short interfaceBoardStatus() const;
    // 设置接口板状态
    bool setInterfaceBoardStatus(short type);


    // 获取系统时钟计数值
    unsigned long clock() const;

    // 获取高精度时钟计数值
    unsigned long clockHighPrecision() const;
    // 延时（毫秒级）
    bool delay(unsigned short milliseconds);
    // 高精度延时（微秒级）
    bool delayHighPrecision(unsigned short microseconds);


    // 开启中断（注册回调）
    bool interruptOn(short (*pCallback)(TInterrupt));
    // 关闭中断
    bool interruptOff();
    // 设置中断掩码
    bool setInterruptMask(long mask);
    // 获取中断掩码
    long interruptMask() const;
    // 触发软件中断
    bool triggerInterrupt(short param);


    // 获取板卡 UUID
    QString uuid() const;
    // 设置板卡 UUID
    bool setUuid(const QString& code);


    // 获取/设置 Display DIP 状态
    short displayDip() const;
    bool setDisplayDip(short mode);
    // 获取设备共享最大数
    bool setDeviceShareMax(short count);
    // 获取最后一次错误码
    short lastError() const { return m_lastError; }
    // 获取最后一次错误描述
    QString lastErrorString() const;

signals:
    // 板卡已打开
    void opened();
    // 板卡已关闭
    void closed();
    // 发生错误 (错误码, 错误描述)
    void errorOccurred(short errorCode, const QString& errorMsg);

private:
    bool m_isOpen = false;
    short m_cardNo = 0;
    short m_lastError = 0;
};

#endif // BOARDMGR_H
