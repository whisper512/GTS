#include "TotalMgr.h"
#include "BoardMgr.h"
#include "AxisMgr.h"
#include "MotionMgr.h"
#include "InterpolationMgr.h"
#include "IOMgr.h"
#include "FeedbackMgr.h"
#include "ConfigMgr.h"

CTotalMgr::CTotalMgr(QObject* parent)
    : QObject(parent)
{   
    m_boardMgr = std::make_unique<BoardMgr>(this);
    m_axisMgr = std::make_unique<AxisMgr>(this);
    m_motionMgr = std::make_unique<MotionMgr>(this);
    m_interpolationMgr = std::make_unique<InterpolationMgr>(this);
    m_ioMgr = std::make_unique<IOMgr>(this);
    m_feedbackMgr = std::make_unique<FeedbackMgr>(this);
    m_configMgr = std::make_unique<ConfigMgr>(this);

    m_boardMgr->setTotalMgr(this);
}

CTotalMgr::~CTotalMgr() {
    shutdown();
}

bool CTotalMgr::initialize(short channel) {
    if (m_initialized) {
        
        shutdown();
    }
    if (!m_boardMgr->open(channel)) {
        QString err = QStringLiteral("板卡打开失败: %1")
            .arg(m_boardMgr->lastErrorString());
        return false;
    }

    m_initialized = true;
    return true;
}

void CTotalMgr::shutdown() {
    if (!m_initialized) return;

    
    m_boardMgr->close();

    m_initialized = false;
}

void CTotalMgr::emergencyStop() {
    if (!m_initialized) return;
    m_boardMgr->reset();
}

QString CTotalMgr::lastErrorString() const {
    if (m_boardMgr) {
        return m_boardMgr->lastErrorString();
    }
    return QStringLiteral("无错误");
}
