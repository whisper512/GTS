#include "CoordEngine.h"
#include "GtsCoordMgr.h"
#include "ControllerData.h"

CoordEngine::CoordEngine(QObject* parent)
    : QObject(parent)
{
    m_pollTimer = new QTimer(this);
    connect(m_pollTimer, &QTimer::timeout, this, &CoordEngine::onPoll);
}

CoordEngine::~CoordEngine()
{
    stop();
    m_coord = nullptr;
}

bool CoordEngine::sim() const
{
    return m_coordCfg ? m_coordCfg->enableSim : true;
}

bool CoordEngine::staticMode() const
{
    return m_coordCfg && m_coordCfg->mode == CoordMode::Static;
}

void CoordEngine::loadTable(const CoordTable& table)
{
    stop();
    m_table = table;
    m_current = -1;
}

void CoordEngine::start()
{
    if (m_table.empty()) return;

    // 模拟模式: 不调用硬件, 定时器逐段推进
    if (sim()) {
        m_current = 0;
        m_running = true;
        emit started();
        emit segmentStarted(0);
        m_pollTimer->start(m_simSegmentMs);
        return;
    }

    if (!m_coord) return;

    m_coord->clear(m_crd);
    m_current = 0;
    m_running = true;

    if (staticMode()) {
        // 静态模式: 一次性把所有段塞满缓冲区
        for (int i = 0; i < (int)m_table.size(); ++i) {
            if (!executeSegment(i)) {
                stop();
                return;
            }
        }
        m_coord->start(1 << m_crd);
    }
    else {
        // 动态模式: 先塞第一段再启动
        if (!executeSegment(m_current)) {
            stop();
            return;
        }
        m_coord->start(1 << m_crd);
    }

    // 插补状态轮询定时器
    m_pollTimer->start(50);
    emit started();
    emit segmentStarted(0);
}

void CoordEngine::stop()
{
    m_pollTimer->stop();
    if (m_running && m_coord && !sim()) {
        m_coord->stop(m_crd);
    }
    m_running = false;
    m_current = -1;
    emit stopped();
}

void CoordEngine::reset()
{
    stop();
    m_table.clear();
}

void CoordEngine::onPoll()
{
    if (!m_running || m_current < 0) return;

    // 模拟模式: 定时器到点即视为当前段完成
    if (sim()) {
        emit segmentDone(m_current);
        m_current++;

        if (m_current >= (int)m_table.size()) {
            m_pollTimer->stop();
            m_current = -1;
            m_running = false;
            emit allDone();
            return;
        }

        emit segmentStarted(m_current);
        return;
    }

    if (!m_coord) return;

    // 静态模式: 查询剩余段数反推执行进度
    if (staticMode()) {
        long remain = m_coord->getRemainingSegment(m_crd);
        if (remain < 0) return; // 查询失败, 等待下次轮询

        int completed = (int)m_table.size() - (int)remain;
        while (m_current < completed) {
            emit segmentDone(m_current);
            m_current++;
            if (m_current < (int)m_table.size()) {
                emit segmentStarted(m_current);
            }
        }

        if (m_current >= (int)m_table.size()) {
            m_pollTimer->stop();
            m_current = -1;
            m_running = false;
            emit allDone();
        }
        return;
    }

    // 动态模式: 查询插补状态, 完成一段补下一段
    short running = 0;
    long segment = 0;
    if (!m_coord->status(m_crd, running, segment)) {
        // status query failed, stop
        stop();
        emit errorOccurred(m_current, QStringLiteral("查询插补状态失败"));
        return;
    }

    if (!running) {
        // 当前段执行完成
        emit segmentDone(m_current);
        m_current++;

        if (m_current >= (int)m_table.size()) {
            m_pollTimer->stop();
            m_current = -1;
            m_running = false;
            emit allDone();
            return;
        }

        executeSegment(m_current);
        emit segmentStarted(m_current);
    }
}

bool CoordEngine::executeSegment(int index)
{
    if (index < 0 || index >= (int)m_table.size()) return false;

    const auto& seg = m_table[index];

    bool ok = false;
    if (seg.type == SegmentType::Arc && seg.r != 0.0) {
        short dir = (seg.dir == ArcDir::CW) ? 0 : 1;
        ok = m_coord->arcXYByRadius(m_crd,
            static_cast<long>(seg.x), static_cast<long>(seg.y),
            seg.r, dir, seg.f, seg.f); // 先复用 f 作为加速度
    }
    else {
        ok = m_coord->lineXY(m_crd,
            static_cast<long>(seg.x), static_cast<long>(seg.y),
            seg.f, seg.f); // 先复用 f 作为加速度
    }

    if (!ok) {
        emit errorOccurred(index, QStringLiteral("插补段 %1 加载失败").arg(index + 1));
        return false;
    }
    return true;
}

void CoordEngine::advance()
{
}
