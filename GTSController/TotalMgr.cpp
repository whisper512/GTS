#include "TotalMgr.h"
#include "BoardMgr.h"
#include "AxisMgr.h"
#include "MotionMgr.h"
#include "InterpolationMgr.h"
#include "IOMgr.h"
#include "FeedbackMgr.h"
#include "ConfigMgr.h"

TotalMgr::TotalMgr(QObject* parent)
    : QObject(parent)
{   
    m_boardMgr = std::make_unique<BoardMgr>(this);
    m_axisMgr = std::make_unique<AxisMgr>(this);
    m_motionMgr = std::make_unique<MotionMgr>(this);
    m_interpolationMgr = std::make_unique<InterpolationMgr>(this);
    m_ioMgr = std::make_unique<IOMgr>(this);
    m_feedbackMgr = std::make_unique<FeedbackMgr>(this);
    m_configMgr = std::make_unique<ConfigMgr>(this);
}

TotalMgr::~TotalMgr() {
    shutdown();
}

bool TotalMgr::initialize(short channel) {
    if (m_initialized) {
        
        shutdown();
    }
    if (!m_boardMgr->open(channel)) {
        QString err = QStringLiteral("板卡打开失败: %1")
            .arg(m_boardMgr->lastErrorString());
        emit errorOccurred(err);
        return false;
    }

    m_initialized = true;
    emit initialized();
    return true;
}

void TotalMgr::shutdown() {
    if (!m_initialized) return;

    
    m_boardMgr->close();

    m_initialized = false;
    emit shutdowned();
}

void TotalMgr::emergencyStop() {
    if (!m_initialized) return;
    m_boardMgr->reset();

    emit errorOccurred(QStringLiteral("紧急停止已触发"));
}

QString TotalMgr::lastErrorString() const {
    if (m_boardMgr) {
        return m_boardMgr->lastErrorString();
    }
    return QStringLiteral("无错误");
}
