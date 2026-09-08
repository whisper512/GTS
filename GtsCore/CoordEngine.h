#pragma once
#include <QObject>
#include <QTimer>

#include "CoordData.h"

class CoordMgr;
struct CoordCfg;

// ============================================================
// CoordEngine — 插补引擎
// 职责: 持有插补表, 逐段驱动 CoordMgr 执行, 管理执行状态
// ============================================================

class CoordEngine : public QObject
{
    Q_OBJECT

public:
    explicit CoordEngine(QObject* parent = nullptr);
    ~CoordEngine();

    // 注入依赖
    void injectDependencies(CoordMgr* mgr, short crd, CoordCfg* cfg);
    // 模拟模式下每段的兜底执行时长 (ms)，实际时长按 长度/速度 计算
    void setSimSegmentMs(int ms) { m_simSegmentMs = ms; }

    // 加载插补表
    void loadTable(const CoordTable& table);
    const CoordTable& table() const { return m_table; }

    // 执行控制
    void start();
    void stop();
    void reset();

    // 状态
    int currentIndex() const { return m_current; }
    bool isRunning() const { return m_running; }
    int totalSegments() const { return (int)m_table.size(); }

signals:
    void started();
    void segmentStarted(int index);
    void segmentDone(int index);
    void allDone();
    void stopped();
    void errorOccurred(int index, const QString& msg);

private slots:
    void onPoll();

private:
    // 运控卡加载插补段
    bool executeSegment(int index);
    // 前瞻
    void advance();
    // 是否模拟模式
    bool sim() const;
    // 是否静态模式
    bool staticMode() const;
    // 计算某段的模拟执行时长 (ms) = 路径长度 / 速度 F
    int segmentDurationMs(int index) const;

    CoordMgr* m_coord = nullptr;
    CoordCfg* m_coordCfg = nullptr;
    short m_crd = 0;
    CoordTable m_table;
    int m_current = -1;
    bool m_running = false;
    int m_simSegmentMs = 300;
    QTimer* m_pollTimer = nullptr;
};
