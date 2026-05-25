#ifndef TOTALMGR_H
#define TOTALMGR_H

#include <QObject>
#include <memory>


class BoardMgr;
class AxisMgr;
class ConfigMgr;
class FeedbackMgr;
class InterpolationMgr;
class IOMgr;
class MotionMgr;

// TotalMgr — 总管理器
class TotalMgr : public QObject 
{
    Q_OBJECT

private:
    bool m_initialized = false;
    std::unique_ptr<BoardMgr> m_boardMgr;
    std::unique_ptr<AxisMgr> m_axisMgr;
    std::unique_ptr<MotionMgr> m_motionMgr;
    std::unique_ptr<InterpolationMgr> m_interpolationMgr;
    std::unique_ptr<IOMgr> m_ioMgr;
    std::unique_ptr<ConfigMgr> m_configMgr;
    std::unique_ptr<FeedbackMgr> m_feedbackMgr;

public:
    explicit TotalMgr(QObject* parent = nullptr);
    ~TotalMgr();

    bool initialize(short channel = 0);
    void shutdown();

    bool isInitialized() const { return m_initialized; }
    // 板卡管理器
    BoardMgr* board() const { return m_boardMgr.get(); }
    // 轴管理器
    AxisMgr* axis() const { return m_axisMgr.get(); }
    // 运动管理器
    MotionMgr* motion() const { return m_motionMgr.get(); }
    // 插补管理器
    InterpolationMgr* interpolation() const { return m_interpolationMgr.get(); }
    // IO管理器
    IOMgr* io() const { return m_ioMgr.get(); }
    // 反馈管理器
    FeedbackMgr* feedback() const { return m_feedbackMgr.get(); }
    // 配置管理器
    ConfigMgr* config() const { return m_configMgr.get(); }

    void emergencyStop();
    // 获取最近一次错误字符串
    QString lastErrorString() const;

signals:
    // 初始化完成
    void initialized();
    // 已关闭
    void shutdowned();
    // 发生错误
    void errorOccurred(const QString& errorMsg);


};

#endif // TOTALMGR_H
