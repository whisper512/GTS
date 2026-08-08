#include "CoordEngine.h"
#include "GtsCoordMgr.h"

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

void CoordEngine::loadTable(const CoordTable& table)
{
    stop();
    m_table = table;
    m_current = -1;
}

void CoordEngine::start()
{
    if (!m_coord || m_table.empty()) return;

    m_coord->clear(m_crd);
    m_current = 0;
    m_running = true;
    executeSegment(m_current);
    m_coord->start(1 << m_crd);
    m_pollTimer->start(50);
    emit started();
}

void CoordEngine::stop()
{
    m_pollTimer->stop();
    if (m_running && m_coord) {
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
    if (!m_running || !m_coord || m_current < 0) return;

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
    }
}

void CoordEngine::executeSegment(int index)
{
    if (index < 0 || index >= (int)m_table.size()) return;

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
        stop();
        emit errorOccurred(index, QStringLiteral("插补段 %1 加载失败").arg(index + 1));
        return;
    }

    emit segmentStarted(index);
}

void CoordEngine::advance()
{
}
