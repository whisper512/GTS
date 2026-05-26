#pragma once
#include <QWidget>
#include "ui_BoradWidget.h"
class CTotalMgr;

class CBoardWidget : public QWidget
{
	Q_OBJECT

public:
	CBoardWidget(QWidget* parent = nullptr, CTotalMgr* mgr = nullptr);
	~CBoardWidget();

private:
	Ui::BoardWidgetClass ui;
	CTotalMgr* m_pTotalMgr = nullptr;

	void ConnectPrivateSignal();

public slots:

private slots:
	void OnBtnClick();

};

