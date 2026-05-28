#pragma once
// 数据结构


// 板卡信息
struct stuCardInfo {
    short cardNum;
    short cardType;
};

// 驱动版本
struct stuDriverVersion {
    unsigned short mainVer;
    unsigned short slaveVer;
};

// 时钟
struct stuClock {
    unsigned long sysClock;            // 系统时钟
    unsigned long highPrecClock;       // 高精度时钟

    stuClock() : sysClock(0), highPrecClock(0) {}
};

// 点位运动(trap)参数
struct stuTrapParam
{
    unsigned int  stepSize; // 步长
    double vel;             // 速度
    double acc;             // 加速度
    double dec;             // 减速度
    int somoothTime;        // 平滑时间
    int cycleTimes;         // 循环次数
    int Delay;              // 到位延时

    stuTrapParam() {
        stepSize = 10000;
        vel = 0.0;
        acc = 0.0;
        dec = 0.0;
        somoothTime = 0;
        cycleTimes = 0;
        Delay = 0;
    }
};

// 轴信息
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
    stuTrapParam trapParam; // 点位运动(trap)参数

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
        trapParam = stuTrapParam();
    }
    // 解析轴状态
    void parseStatus(long status) {
        AxisStatus = status;
        bAlarm = (status & 0x02) != 0;
        bMError = (status & 0x10) != 0;
        bPosLimit = (status & 0x20) != 0;
        bNegLimit = (status & 0x40) != 0;
        bSmoothStop = (status & 0x80) != 0;
        bAbruptStop = (status & 0x100) != 0;
        bServoOn = (status & 0x200) != 0;
        bMotion = (status & 0x400) != 0;
    }
};

// 运动模式转字符串
static QString motionModeToString(long mode)
{
    switch (mode) {
    case 0:  return QStringLiteral("点位运动(Trap)");
    case 1:  return QStringLiteral("Jog");
    case 2:  return QStringLiteral("PT");
    case 3:  return QStringLiteral("电子齿轮(Gear)");
    case 4:  return QStringLiteral("Follow");
    case 5:  return QStringLiteral("插补(Interpolation)");
    case 6:  return QStringLiteral("PVT");
    default: return QStringLiteral("未知(%1)").arg(mode);
    }
}
