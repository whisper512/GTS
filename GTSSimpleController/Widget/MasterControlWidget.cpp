#include "MasterControlWidget.h"
#include "../Mgr/TotalMgr.h"


CMasterControlWidget::CMasterControlWidget(QWidget *parent,  CTotalMgr* mgr)
	: QWidget(parent)
	, m_pTotalMgr(mgr)
{
	ui.setupUi(this);
}

CMasterControlWidget::~CMasterControlWidget()
{}

