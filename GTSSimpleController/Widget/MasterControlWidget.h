#pragma once

#include <QWidget>
#include "ui_MasterControlWidget.h"

class CTotalMgr;

class CMasterControlWidget : public QWidget
{
	Q_OBJECT

public:
	CMasterControlWidget(QWidget *parent = nullptr,CTotalMgr * mgr = nullptr);
	~CMasterControlWidget();

private:
	Ui::CMasterControlWidgetClass ui;
	CTotalMgr * m_pTotalMgr;
};

