#ifndef TOTALMGR_H
#define TOTALMGR_H

#include <QObject>
#include <QColor>
#include <QTimer>
#include <memory>
#include <vector>

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
    // 配置
    stuConfig m_cfg;

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

    // JSON 读写
    bool loadAxisConfig(const QString& filePath = QString());
    bool saveAxisConfig(const QString& filePath = QString()) const;
    void readAllAxisConfigFromBoard();
    void applyAllAxisConfigToBoard();
    QString axisConfigPath() const;

    // 控制模式
    void setControlMode(short axis, ControlMode mode);
    ControlMode controlMode(short axis) const;

    // profile 当量
    void setProfileScale(short axis, long alpha, long beta);
    long profileScaleAlpha(short axis) const;
    long profileScaleBeta(short axis) const;

    // encoder 当量
    void setEncoderScale(short axis, long alpha, long beta);
    long encoderScaleAlpha(short axis) const;
    long encoderScaleBeta(short axis) const;

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
