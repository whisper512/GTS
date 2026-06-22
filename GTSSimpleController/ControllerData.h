#pragma once

#define GTS_NO_Motor      // 无电机模式

// 输入类型
enum class DIType : short
{ 
    LimitPositive = 0,   // MC_LIMIT_POSITIVE  正限位
    LimitNegative = 1,   // MC_LIMIT_NEGATIVE  负限位
    Alarm = 2,           // MC_ALARM           驱动报警
    Home = 3,            // MC_HOME            原点
    GPI = 4,             // MC_GPI             通用输入
    Arrive = 5,          // MC_ARRIVE          电机到位
    MPG = 6              // MC_MPG             手轮
};

inline QString DITypeToString(DIType type)
{
    switch (type) {
    case DIType::LimitPositive: return QStringLiteral("正限位");
    case DIType::LimitNegative: return QStringLiteral("负限位");
    case DIType::Alarm:         return QStringLiteral("驱动报警");
    case DIType::Home:          return QStringLiteral("原点");
    case DIType::GPI:           return QStringLiteral("通用输入");
    case DIType::Arrive:        return QStringLiteral("电机到位");
    case DIType::MPG:           return QStringLiteral("手轮");
    default:                     return QStringLiteral("未知");
    }
}

// 输出类型
enum class DOType : short
{
    ServoOn = 0,   // MC_SERVO_ON  伺服使能
    AlmClear = 1,  // MC_ALM_CLEAR 报警清除
    GPO = 2        // MC_GPO       通用输出
};

// 脉冲输出模式
enum class PulseMode : short
{
    PulseDir = 0,   // 脉冲 + 方向
    CCW_CW = 1      // 双脉冲（正转/反转）
};

// IO极性
enum class IOPolarity : short
{
    Normal = 0,    // 正常
    Reverse = 1    // 取反
};

// 脉冲计数源
enum class PulseCountSource : short
{
    Encoder = 0,     // 编码器
    PulseCounter = 1 // 脉冲计数器
};

// 触发沿
enum class TriggerEdge : short
{
    Rising = 0,    // 上升沿
    Falling = 1    // 下降沿
};

// 控制模式
enum class ControlMode : short
{
    ClosedLoop = 0,   // 闭环:有电机 + 编码器
    OpenLoop = 1,     // 开环:有电机 + 脉冲计数器
    Simulation = 2    // 调试:无电机 + 脉冲计数器
};



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

// DI 状态
struct stuDI
{
    std::vector<int> vecPLimit;    // 正限位，8 位
    std::vector<int> vecNLimit;    // 负限位，8 位
    std::vector<int> vecAlarm;     // 驱动报警，8 位
    std::vector<int> vecHome;      // 原点信号，8 位
    std::vector<int> vecGPI;       // 通用输入1，16 位
    std::vector<int> vecArrive;    // 电机到位，8 位
    std::vector<int> vecHandwheel; // 手轮输入2，8 位

    stuDI() {
        vecPLimit.resize(8, 0);
        vecNLimit.resize(8, 0);
        vecAlarm.resize(8, 0);
        vecHome.resize(8, 0);
        vecGPI.resize(16, 0);
        vecArrive.resize(8, 0);
        vecHandwheel.resize(8, 0);
    }

    // 展平为 64 位，与表格行号一一对应
    std::vector<int> toFlatVector() const {
        std::vector<int> flat;
        flat.insert(flat.end(), vecPLimit.begin(), vecPLimit.end());   // 0~7
        flat.insert(flat.end(), vecNLimit.begin(), vecNLimit.end());   // 8~15
        flat.insert(flat.end(), vecAlarm.begin(), vecAlarm.end());    // 16~23
        flat.insert(flat.end(), vecHome.begin(), vecHome.end());     // 24~31
        flat.insert(flat.end(), vecGPI.begin(), vecGPI.end());     // 32~47
        flat.insert(flat.end(), vecArrive.begin(), vecArrive.end());   // 48~55
        flat.insert(flat.end(), vecHandwheel.begin(), vecHandwheel.end());     // 56~63
        return flat;
    }
};

// DO 状态
struct stuDO
{
    std::vector<int> vecServoOn;   // 伺服使能，8 位
    std::vector<int> vecAlmClear;  // 报警清除，8 位
    std::vector<int> vecGPO;       // 通用输出，16 位

    stuDO() {
        vecServoOn.resize(8, 0);
        vecAlmClear.resize(8, 0);
        vecGPO.resize(16, 0);
    }

    std::vector<int> toFlatVector() const {
        std::vector<int> flat;
        flat.insert(flat.end(), vecServoOn.begin(), vecServoOn.end());   // 0~7
        flat.insert(flat.end(), vecAlmClear.begin(), vecAlmClear.end());  // 8~15
        flat.insert(flat.end(), vecGPO.begin(), vecGPO.end());       // 16~31
        return flat;
    }
};

// 时钟
struct stuClock {
    unsigned long sysClock;            // 系统时钟
    unsigned long highPrecClock;       // 高精度时钟

    stuClock() : sysClock(0), highPrecClock(0) {}
};

struct stuScaleFactor
{
    long alpha = 1;
    long beta = 1;
};


struct stuConfig
{
    int axisCount = 4;

    // 规划器当量
    stuScaleFactor profileScale[4];
    // 编码器当量
    stuScaleFactor encScale[4];
    // 控制模式
    ControlMode ctrlMode[4] = { ControlMode::ClosedLoop,ControlMode::ClosedLoop, ControlMode::ClosedLoop,ControlMode::ClosedLoop };

    // DAC
    short dacBias[4] = { 0, 0, 0, 0 };
    short dacLimit[4] = { 32767, 32767, 32767, 32767 };
    // 跟随误差
    long followingErrorLimit[4] = { 32767, 32767, 32767, 32767 };
    // 停止减速
    double smoothStopDec[4] = { 100.0, 100.0, 100.0, 100.0 };
    double estopDec[4] = { 1000.0, 1000.0, 1000.0, 1000.0 };

};


// 点位运动(trap)参数
struct stuTrapParam
{
    double dMotionVel;      // 运动速度
    double lengthMm;        // 步长 mm
    double acc;             // 加速度
    double dec;             // 减速度
    int somoothTime;        // 平滑时间
    int cycleTimes;         // 循环次数
    int Delay;              // 到位延时

    stuTrapParam()
        : dMotionVel(1.0)
        , lengthMm(10.0)
        , acc(1.0)
        , dec(1.0)
        , somoothTime(0)
        , cycleTimes(0)
        , Delay(0)
    {
    }
};

// jog运动参数
struct stuJogParam
{
    double dMotionVel;      // 运动速度
    double acc;             // 加速度
    double dec;             // 减速度
    double smoothTime;      // 平滑时间

    stuJogParam()
        : dMotionVel(5.0)
        , acc(1.0)
        , dec(1.0)
        , smoothTime(0.0)
    {
    }
};

// 轴信息
struct stuAxis
{
    // 轴状态
    short axisIndex;   // 轴号1-4
    bool bAlarm;       // 报警
    bool bMError;      // 跟随误差越限
    bool bPosLimit;    // 正限位触发
    bool bNegLimit;    // 负限位触发
    bool bSmoothStop;  // 平滑停止
    bool bAbruptStop;  // 急停
    bool bServoOn;     // 伺服使能
    bool bMotion;      // 规划器运动

    // ===== 规划器 =====
    double dPrfPosOriginal;    // 规划位置原始数据,已经经过当量换算
    double dPrfVelOriginal;    // 规划速度原始数据,已经经过当量换算
    double dPrfAccOriginal;    // 规划加速度原始数据,已经经过当量换算
    double dPrfPosMm;  // mm
    double dPrfVelMm;  // mm/s
    double dPrfAccMm;  // mm/s²
    long lPrfMode;     // 运动模式
    long AxisStatus;   // 轴状态

    // ===== 编码器 =====
    double dEncPos;    // 编码器位置
    double dEncVel;    // 编码器速度
    double dEncPosMm;  // 编码器换算位置(单位:mm)
    double dEncVelMm;  // 编码器换算速度(单位:mm/s)

    stuTrapParam trapParam; // 点位运动(trap)参数
    stuJogParam jogParam;   // jog运动参数

    stuAxis()
        : axisIndex(0)
        , bAlarm(false)
        , bMError(false)
        , bPosLimit(false)
        , bNegLimit(false)
        , bSmoothStop(false)
        , bAbruptStop(false)
        , bServoOn(false)
        , bMotion(false)
        , dPrfPosOriginal(0.0)
        , dPrfVelOriginal(0.0)
        , dPrfAccOriginal(0.0)
        , dPrfPosMm(0.0)
        , dPrfVelMm(0.0)
        , dPrfAccMm(0.0)
        , lPrfMode(0)
        , AxisStatus(0)
        , dEncPos(0.0)
        , dEncVel(0.0)
        , dEncPosMm(0.0)
        , trapParam()
        , jogParam()
    {
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
