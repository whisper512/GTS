#ifndef AXISMGR_H
#define AXISMGR_H

#include <QObject>
#include <QString>
#include <Vector>
#include "GtsHal.h"

struct stuAxis
{
    short axisIndex;   // 轴号1-4；
    bool bAlarm;       // 报警
    bool bMError;      // 跟随误差越限
    bool bPosLimit;    // 正限位触发
    bool bNegLimit;    // 负限位触发
    bool bSmoothStop;  // 平滑停止
    bool bAbruptStop;  // 急停
    bool bServoOn;     // 伺服使能
    bool bMotion;      // 规划器运动
    double dCurPos;    // 当前位置
    double dPrfPos;    // 规划位置
    double dCurVel;    // 当前速度
    double dPrfVel;    // 规划速度
    double dCurAcc;    // 当前加速度
    double dPrfAcc;    // 规划加速度
    long lPrfMode;     // 运动模式
    long AxisStatus;   // 轴状态

    stuAxis() {
        axisIndex = 0;
        bAlarm = false;
        bMError = false;
        bPosLimit = false;
        bNegLimit = false;
        bSmoothStop = false;
        bAbruptStop = false;
        bServoOn = false;
        bMotion = false;
        dCurPos = 0.0;
        dPrfPos = 0.0;
        dCurVel = 0.0;
        dPrfVel = 0.0;
        dCurAcc = 0.0;
        dPrfAcc = 0.0;
        lPrfMode = 0;
        AxisStatus = 0;
    }
    // 解析轴状态
    void parseStatus(long status) {
        AxisStatus = status;
        bAlarm = (status & 0x02) != 0;        // 伺服报警
        bMError = (status & 0x10) != 0;       // 跟随误差越限
        bPosLimit = (status & 0x04) != 0;     // 正限位
        bNegLimit = (status & 0x08) != 0;     // 负限位
        bSmoothStop = (status & 0x40) != 0;   // 急停
        bServoOn = (status & 0x01) != 0;      // 伺服使能
        bMotion = (status & 0x20) != 0;       // 运动中
    }
};

class CTotalMgr;

class AxisMgr : public QObject {
    Q_OBJECT

private:
    short m_axisCount = 4;
    mutable short m_lastError = 0;
    std::vector<stuAxis> m_vecAxis[4];
    CTotalMgr* m_pTotalMgr = nullptr;

public:
    explicit AxisMgr(QObject* parent = nullptr);
    ~AxisMgr();
    void setTotalMgr(CTotalMgr* mgr) { m_pTotalMgr = mgr; }

    // 获取轴状态
    stuAxis getAxisInfo(short axis);
    

public:
    // 使能单个轴
    bool enable(short axis);
    // 禁止单个轴
    bool disable(short axis);
    // 使能多个轴(通过位掩码)
    bool enableMulti(unsigned long mask);
    // 禁止多个轴(通过位掩码)
    bool disableMulti(unsigned long mask);
    // 使能所有轴
    bool enableAll();
    // 禁止所有轴
    bool disableAll();
    // 查询单个轴是否已使能
    bool isEnabled(short axis) ;
    // 设置/获取轴使能时的延迟时间ms
    bool setOnDelayTime(unsigned short ms);
    unsigned short onDelayTime() ;
    // 停止单个轴
    // @param option 0=急停(立即停止)  1=减速停止
    bool stop(short axis, long option = 0);
    // 停止所有轴
    bool stopAll(long option = 0);
    // 停止多个轴(通过位掩码)
    bool stopMulti(long mask, long option = 0);
    // 开启报警
    bool alarmOn(short axis);
    // 关闭报警
    bool alarmOff(short axis);
    // 查询是否有报警
    bool isAlarm(short axis);
    // 开启限位（可指定正/负限位，-1=全部）
    bool limitOn(short axis, short limitType = -1);
    // 关闭限位
    bool limitOff(short axis, short limitType = -1);
    // 设置限位电平极性
    bool setLimitSense(unsigned short sense);
    // 设置软限位
    bool setSoftLimit(short axis, long positive, long negative);
    // 获取软限位
    bool getSoftLimit(short axis, long& positive, long& negative);
    // 获取轴状态(通过位掩码)
    long status(short axis);
    // 清除轴状态
    bool clearStatus(short axis);
    // 清零轴位置
    bool zeroPosition(short axis);
    // 同步多轴位置
    bool syncPosition(long mask);
    // 设置控制模式
    bool setControlMode(short axis, short mode);
    // 设置轴模式
    bool setAxisMode(short axis, short mode);
    // 获取轴模式
    short getAxisMode(short axis) ;
    // 设置跟随误差极限
    bool setFollowErrorLimit(short control, long error);
    // 获取跟随误差极限
    long getFollowErrorLimit(short control) ;
    // 设置跟随误差模式
    bool setFollowErrorMode(short axis, short mode);
    // 获取跟随误差模式
    short getFollowErrorMode(short axis);
    // 设置停止减速参数
    bool setStopDecel(short profile, double smooth, double abrupt);
    // 获取停止减速参数
    bool getStopDecel(short profile, double& smooth, double& abrupt);
    // 设置停止触发 IO
    bool setStopIO(short axis, short stopType, short inputType, short inputIndex);
    // 获取轴编码器位置
    double encoderPosition(short axis);
    // 获取轴编码器速度
    double encoderVelocity(short axis) ;
    // 获取轴编码器加速度
    double encoderAcceleration(short axis) ;
    // 获取轴跟踪误差
    double trackingError(short axis);
    // 轴号是否有效
    bool isValidAxis(short axis);
    // 获取最后一次错误码
    short lastError() { return m_lastError; }
    // 获取最后一次错误描述
    QString lastErrorString() ;
    // 获取轴状态文本描述
    static QString statusToString(long sts);

signals:
    // 发生错误
    void errorOccurred(short axis, short errorCode, const QString& errorMsg);

};

#endif // AXISMGR_H
