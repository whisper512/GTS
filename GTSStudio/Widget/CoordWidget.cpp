#include "CoordWidget.h"
#include <QLabel>
#include <QVBoxLayout>

CoordWidget::CoordWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

CoordWidget::~CoordWidget()
{
    m_gtsMgr = nullptr;
}

void CoordWidget::setGtsTotalMgr(GtsMgr* mgr)
{
    m_gtsMgr = mgr;
}
