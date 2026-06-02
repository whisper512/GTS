#pragma once
// 数据结构

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

inline QString dioTypeToString(DIType type)
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
    GPO = 2        // MC_GPO        通用输出
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

// 脉冲技术源
enum class PulseCountSource : short
{
    Encoder = 0,   // 编码器
    PulseCounter = 1 // 脉冲计数器
};

// 触发沿
enum class TriggerEdge : short
{
    Rising = 0,   // 上升沿
    Falling = 1    // 下降沿
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

// 轴配置
struct stuAxisConfig
{
    int axisIndex;              // 轴号
    bool bActivate;             // 激活
    DIType servoAlarm;          // 驱动报警输入类型
    int servoAlarmIndex;        // 驱动报警输入索引
    DIType PLimit;              // 正限位输入类型
    int PLimitIndex;            // 正限位输入索引
    DIType NLimit;              // 负限位输入类型
    int NLimitIndex;            // 负限位输入索引
    DIType smoothStop;          // 平滑停止输入类型
    int smoothStopIndex;        // 平滑停止输入索引
    DIType EStop;               // 急停输入类型
    int EStopIndex;             // 急停输入索引
    int profileEquivalentAlpha; // 脉冲当量系数A
    int profileEquivalentBeta;  // 脉冲当量系数B
    int encoderEquivalentAlpha; // 编码器当量系数A
    int encoderEquivalentBeta;  // 编码器当量系数B
    stuAxisConfig()
        : axisIndex(0)
        , bActivate(false)
        , servoAlarm(DIType::Alarm)
        , servoAlarmIndex(1)
        , PLimit(DIType::LimitPositive)
        , PLimitIndex(1)
        , NLimit(DIType::LimitNegative)
        , NLimitIndex(1)
        , smoothStop(DIType::GPI)
        , smoothStopIndex(1)
        , EStop(DIType::GPI)
        , EStopIndex(1)
        , profileEquivalentAlpha(1)
        , profileEquivalentBeta(1)
        , encoderEquivalentAlpha(1)
        , encoderEquivalentBeta(1)
    {
    }
};
// step配置
struct stuStepConfig
{
    int stepIndex;             // 步进号
    PulseMode pulseOutputMode; // 脉冲输出模式
    stuStepConfig()
        : stepIndex(0)
        , pulseOutputMode(PulseMode::PulseDir)
    {
    }
};
// dac配置
struct stuDacConfig
{
    int dacIndex;                       // DAC号
    int associateControl;               // 关联控制
    IOPolarity outputVoltagePolarity;   // 输出电压极性
    int zeroOffsetCompensation;         // 零漂补偿
    int outputVoltageSaturationLimit;   // 输出电压饱和限制
    stuDacConfig()
        : dacIndex(0)
        , associateControl(0)
        , outputVoltagePolarity(IOPolarity::Normal)
        , zeroOffsetCompensation(0)
        , outputVoltageSaturationLimit(32767)
    {
    }
};
// encoder配置
struct stuEncoderConfig
{
    int encoderIndex;                   // 编码器号
    IOPolarity inputPlusePolarity;      // 输入脉冲极性
    PulseCountSource pulseCountSource;  // 脉冲计数源
    TriggerEdge homeTriggerEdge;        // 回原触发沿
    TriggerEdge indexTriggerEdge;       // 索引触发沿
    stuEncoderConfig()
        : encoderIndex(0)
        , inputPlusePolarity(IOPolarity::Normal)
        , pulseCountSource(PulseCountSource::Encoder)
        , homeTriggerEdge(TriggerEdge::Rising)
        , indexTriggerEdge(TriggerEdge::Rising)
    {
    }
};
// control配置
struct stuControlConfig
{
    int controlIndex;       // 控制号
    int associateAxis;      // 关联轴
    int associateEncoder;   // 关联编码器
    int followingErrorLimit;// 跟随误差限制
    stuControlConfig()
        : controlIndex(0)
        , associateAxis(0)
        , associateEncoder(0)
        , followingErrorLimit(32767)
    {
    }
};
// profile配置
struct stuProfileConfig
{
    int profileIndex;  // 脉冲配置号
    int smoothStopDec; // 平滑停止减速
    int estopDec;
    stuProfileConfig()
        : profileIndex(0)
        , smoothStopDec(100)
        , estopDec(1000)
    {
    }
};
// DI配置
struct stuDIConfig
{
    DIType type;            // 输入类型
    int DIIndex;            // 输入索引
    IOPolarity DIPolarity;  // 输入极性
    int filterTime;         // 滤波时间
    stuDIConfig()
        : type(DIType::GPI)
        , DIIndex(0)
        , DIPolarity(IOPolarity::Normal)
        , filterTime(0)
    {
    }
};
// DO配置
struct stuDOConfig
{
    DOType type;            // 输出类型
    int DOIndex;            // 输出索引
    IOPolarity DOPolarity;  // 输出极性
    int associateAxis;      // 关联轴
    stuDOConfig()
        : type(DOType::GPO)
        , DOIndex(0)
        , DOPolarity(IOPolarity::Normal)
        , associateAxis(0)
    {
    }
};

// 总配置数据
struct stuConfig
{
    int AxisConfigCount;
    int StepConfigCount;
    int DacConfigCount;
    int EncoderConfigCount;
    int ControlConfigCount;
    int ProfileConfigCount;
    int DIConfigCount;
    int DOConfigCount;
    std::vector<stuAxisConfig> vecAxisConfig;
    std::vector<stuStepConfig> vecStepConfig;
    std::vector<stuDacConfig> vecDacConfig;
    std::vector<stuEncoderConfig> vecEncoderConfig;
    std::vector<stuControlConfig> vecControlConfig;
    std::vector<stuProfileConfig> vecProfileConfig;
    std::vector<stuDIConfig> vecDIConfig;
    std::vector<stuDOConfig> vecDOConfig;
    stuConfig()
        : AxisConfigCount(0)
        , StepConfigCount(0)
        , DacConfigCount(0)
        , EncoderConfigCount(0)
        , ControlConfigCount(0)
        , ProfileConfigCount(0)
        , DIConfigCount(0)
        , DOConfigCount(0)
    {
    }
};


// 点位运动(trap)参数
struct stuTrapParam
{
    double dMotionVel;      // 运动速度
    unsigned int  stepSize; // 步长
    double acc;             // 加速度
    double dec;             // 减速度
    int somoothTime;        // 平滑时间
    int cycleTimes;         // 循环次数
    int Delay;              // 到位延时

    stuTrapParam()
        : dMotionVel(1.0)
        , stepSize(10000)
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
    short axisIndex;   // 轴号1-4
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
    double dCurVel;    // 实际速度
    double dPrfVel;    // 规划速度
    double dCurAcc;    // 当前加速度
    double dPrfAcc;    // 规划加速度
    long lPrfMode;     // 运动模式
    long AxisStatus;   // 轴状态
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
        , dCurPos(0.0)
        , dPrfPos(0.0)
        , dCurVel(0.0)
        , dPrfVel(0.0)
        , dCurAcc(0.0)
        , dPrfAcc(0.0)
        , lPrfMode(0)
        , AxisStatus(0)
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
