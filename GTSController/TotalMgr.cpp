#include "TotalMgr.h"
#include "BoardMgr.h"
#include "AxisMgr.h"
#include "MotionMgr.h"
#include "InterpolationMgr.h"
#include "IOMgr.h"
#include "FeedbackMgr.h"

TotalMgr::TotalMgr(QObject* parent)
    : QObject(parent)
{   
    m_board = std::make_unique<BoardMgr>(this);
    m_axis = std::make_unique<AxisMgr>(this);
    m_motion = std::make_unique<MotionMgr>(this);
    m_interpolation = std::make_unique<InterpolationMgr>(this);
    m_io = std::make_unique<IOMgr>(this);
    m_feedback = std::make_unique<FeedbackMgr>(this);
}

TotalMgr::~TotalMgr() {
    shutdown();
}

bool TotalMgr::initialize(short channel) {
    if (m_initialized) {
        
        shutdown();
    }
    if (!m_board->open(channel)) {
        QString err = QStringLiteral("板卡打开失败: %1")
            .arg(m_board->lastErrorString());
        emit errorOccurred(err);
        return false;
    }

    m_initialized = true;
    emit initialized();
    return true;
}

void TotalMgr::shutdown() {
    if (!m_initialized) return;

    
    m_board->close();

    m_initialized = false;
    emit shutdowned();
}

void TotalMgr::emergencyStop() {
    if (!m_initialized) return;
    m_board->reset();

    emit errorOccurred(QStringLiteral("紧急停止已触发"));
}

QString TotalMgr::lastErrorString() const {
    if (m_board) {
        return m_board->lastErrorString();
    }
    return QStringLiteral("无错误");
}
