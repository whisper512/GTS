#pragma once
#include <QObject>
#include <QTimer>

#include "CoordData.h"

class CoordMgr;

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

    void setCoordMgr(CoordMgr* mgr) { m_coord = mgr; }
    void setCrd(short crd) { m_crd = crd; }

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
    void executeSegment(int index);
    void advance();

    CoordMgr* m_coord = nullptr;
    short m_crd = 0;
    CoordTable m_table;
    int m_current = -1;
    bool m_running = false;
    QTimer* m_pollTimer = nullptr;
};
