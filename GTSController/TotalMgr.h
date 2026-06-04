#ifndef TOTALMGR_H
#define TOTALMGR_H

#include <QObject>
#include <QColor>
#include <QTimer>
#include <memory>

#include "BoardMgr.h"
#include "AxisMgr.h"
#include "MotionMgr.h"
#include "InterpolationMgr.h"
#include "IOMgr.h"
#include "FeedbackMgr.h"
#include "ConfigMgr.h"


// TotalMgr — 总管理器
class CTotalMgr : public QObject 
{
    Q_OBJECT

private:
    // 是否初始化
    bool m_initialized = false;
    // 刷新数据定时器
    QTimer* m_pRefreshTimer = nullptr;


    // 轴数
    int m_axisCount = 4;
    // 板卡时钟
    stuClock m_clocks;
    // 轴数据
    std::vector<stuAxis> m_vecAxis;
    // DI
    stuDI m_di;
    // DO
    stuDO m_do;
    // 报警信号状态
    bool m_alarmActive[4] = { false, false, false, false };
    // 报警信号是否可用
    bool m_alarmAvailable[4] = { false, false, false, false };
    // 限位使能状态
    bool m_limitActive[4] = { false, false, false, false };
    // 限位是否可用
    bool m_limitAvailable[4] = { false, false, false, false };
    // 规划器当量 
    long m_profileScaleAlpha[4] = { 1, 1, 1, 1 };
    long m_profileScaleBeta[4] = { 1, 1, 1, 1 };
    // 脉冲输出模式
    short m_stepPulseMode[4] = { 0, 0, 0, 0 };
    // 编码器当量
    long m_encScaleAlpha[4] = { 1, 1, 1, 1 };
    long m_encScaleBeta[4] = { 1, 1, 1, 1 };
    // 编码器配置
    bool m_encInvert[4] = { false, false, false, false };   // 极性: false=正常 true=取反
    bool m_encIsPulse[4] = { false, false, false, false };   // 计数源: false=外部编码器 true=脉冲计数器
    // DAC 配置
    short m_dacBias[4] = { 0, 0, 0, 0 };
    short m_dacLimit[4] = { 32767, 32767, 32767, 32767 };
    // 跟随误差极限 
    long m_followingErrorLimit[4] = { 32767, 32767, 32767, 32767 };
    // 停止减速参数 
    double m_smoothStopDec[4] = { 100.0, 100.0, 100.0, 100.0 };
    double m_estopDec[4] = { 1000.0, 1000.0, 1000.0, 1000.0 };
    // 轴控制模式: 0=闭环(模拟量) 1=开环(脉冲)
    short m_axisCtrlMode[4] = { 0, 0, 0, 0 };
    // 停止 IO 配置 [4 轴][2 类型: 0=急停 1=平滑]
    short m_stopInputType[4][2] = { {0,0}, {0,0}, {0,0}, {0,0} };
    short m_stopInputIndex[4][2] = { {1,1}, {1,1}, {1,1}, {1,1} };
    // GPI 电平极性 (16 位, bit0~bit15 对应 DI1~DI16)
    unsigned short m_gpiSense = 0;

    // 板卡的管理类
    std::unique_ptr<BoardMgr> m_boardMgr;
    std::unique_ptr<AxisMgr> m_axisMgr;
    std::unique_ptr<MotionMgr> m_motionMgr;
    std::unique_ptr<InterpolationMgr> m_interpolationMgr;
    std::unique_ptr<IOMgr> m_ioMgr;
    std::unique_ptr<ConfigMgr> m_configMgr;
    std::unique_ptr<FeedbackMgr> m_feedbackMgr;

public:
    explicit CTotalMgr(QObject* parent = nullptr);
    ~CTotalMgr();

    // 板卡管理器
    BoardMgr* boardMgr() const { return m_boardMgr.get(); }
    // 轴管理器
    AxisMgr* axisMgr() const { return m_axisMgr.get(); }
    // 运动管理器
    MotionMgr* motionMgr() const { return m_motionMgr.get(); }
    // 插补管理器
    InterpolationMgr* interpolationMgr() const { return m_interpolationMgr.get(); }
    // IO管理器
    IOMgr* ioMgr() const { return m_ioMgr.get(); }
    // 反馈管理器
    FeedbackMgr* feedbackMgr() const { return m_feedbackMgr.get(); }
    // 配置管理器
    ConfigMgr* configMgr() const { return m_configMgr.get(); }
   


public:
    // 返回轴数
    int axisCount() const { return m_axisCount; }
    // 获取轴数据的指针
    stuAxis* getAxisRef(int index) { if (index < 0 || index >= (int)m_vecAxis.size()) { return nullptr; }return &m_vecAxis[index]; }
    // 是否正在刷新
    bool isRefreshing() const { return m_pRefreshTimer->isActive(); };
    // 启动刷新实时数据
    void startRefresh(int intervalMs = 500);   
    // 停止刷新实时数据
    void stopRefresh();                   
    // 板卡打开后的初始化
    void initAfterBoardOpened();
    // 板卡关闭后的清理
    void cleanupAfterBoardClosed();

    // 初始化报警状态
    void initAlarmState();
    // 切换报警信号的状态
    bool toggleAlarm(short axis);
    // 获取报警信号的状态
    bool isAlarmActive(short axis) const;
    // 获取报警信号是否可用
    bool isAlarmAvailable(short axis) const;
    // 初始化限位状态
    void initLimitState();
    // 切换限位信号的状态
    bool toggleLimit(short axis);
    // 获取限位信号的状态
    bool isLimitActive(short axis) const;
    // 获取限位信号是否可用
    bool isLimitAvailable(short axis) const;

    // 注意:目前编码器当量无法读取,不调用
    // 读取所有当量
    void readScaleEquivalents();
    // 设置规划器当量
    void setProfileScale(short axis, long alpha, long beta);
    // 设置编码器当量
    void setEncoderScale(short encoder, long alpha, long beta);
    // 获取当量
    long profileScaleAlpha(short axis) const;
    long profileScaleBeta(short axis) const;
    long encScaleAlpha(short encoder) const;
    long encScaleBeta(short encoder) const;
    // 脉冲输出模式
    void initStepPulseMode();
    void setStepPulseMode(short step, short mode);
    short stepPulseMode(short step) const;
    // dac相关
    void readDacConfig();
    void setDacBias(short dac, short bias);
    void setDacLimit(short dac, short limit);
    short dacBias(short dac) const;
    short dacLimit(short dac) const;
    // 误差极限相关
    void readFollowErrorLimit();
    void setFollowErrorLimit(short control, long error);
    long followErrorLimit(short control) const;
    // 停止减速相关
    void readStopDecel();
    void setStopDecel(short profile, double smooth, double abrupt);
    double smoothStopDec(short profile) const;
    double estopDec(short profile) const;
    // 轴控制模式相关
    void initAxisCtrlMode();
    void setAxisCtrlMode(short axis, short mode);
    short axisCtrlMode(short axis) const;
    // 停止 IO 相关
    void initStopIO();
    void setStopIO(short axis, short stopType, short inputType, short inputIndex);
    short stopInputType(short axis, short stopType) const;
    short stopInputIndex(short axis, short stopType) const;
    // GPI 相关
    void initGpiSense();
    void setGpiSenseBit(short diIndex, bool invert);
    bool isGpiSenseInvert(short diIndex) const;
    unsigned short gpiSense() const;
    // 编码器相关
    void initEncoderConfig();
    void setEncoderInvert(short encoder, bool invert);
    void setEncoderPulseCount(short encoder, bool isPulse);
    bool encoderInvert(short encoder) const;
    bool encoderPulseCount(short encoder) const;
signals:
    // 板卡时钟更新
    void boardClockUpdated(const stuClock& clock);
    // 轴实时数据更新
    void axisUpdated(const std::vector<stuAxis>& axisInfo);
    // 轴参数更新
    void axisSettingUpdated(const std::vector<stuAxis>& axisInfo);
    // DI 更新
    void diUpdated(const stuDI& di);
    // DO 更新
    void doUpdated(const stuDO& do_);

    void configChanged();
    
private slots:
    // 定时读取刷新数据
    void onRefreshTimeout();


};

#endif // TOTALMGR_H
