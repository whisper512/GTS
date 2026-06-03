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
