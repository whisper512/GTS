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
class TotalMgr : public QObject {
    Q_OBJECT

private:
    bool m_initialized = false;
    std::unique_ptr<BoardMgr> m_board;
    std::unique_ptr<AxisMgr> m_axis;
    std::unique_ptr<MotionMgr> m_motion;
    std::unique_ptr<InterpolationMgr> m_interpolation;
    std::unique_ptr<IOMgr> m_io;
    std::unique_ptr<ConfigMgr> m_config;
    std::unique_ptr<FeedbackMgr> m_feedback;

public:
    explicit TotalMgr(QObject* parent = nullptr);
    ~TotalMgr();

    bool initialize(short channel = 0);
    void shutdown();

    bool isInitialized() const { return m_initialized; }
    // 板卡管理器
    BoardMgr* board() const { return m_board.get(); }
    // 轴管理器
    AxisMgr* axis() const { return m_axis.get(); }
    // 运动管理器
    MotionMgr* motion() const { return m_motion.get(); }
    // 插补管理器
    InterpolationMgr* interpolation() const { return m_interpolation.get(); }
    // IO管理器
    IOMgr* io() const { return m_io.get(); }
    // 反馈管理器
    FeedbackMgr* feedback() const { return m_feedback.get(); }
    // 配置管理器
    ConfigMgr* config() const { return m_config.get(); }

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
