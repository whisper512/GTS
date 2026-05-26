#pragma once
#include <QWidget>
#include <QTimer>
#include "ui_BoradWidget.h"

class CTotalMgr;
class GTSControllerWidget;

class CBoardWidget : public QWidget
{
	Q_OBJECT

public:
	CBoardWidget(QWidget* parent = nullptr, CTotalMgr* mgr = nullptr);
	~CBoardWidget();

private:
	Ui::BoardWidgetClass ui;
	QTimer* m_pClockTimer = nullptr;
	CTotalMgr* m_pTotalMgr = nullptr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;

	void ConnectPrivateSignal();
	void updateBoardState(bool isOpen);
	void OnOpen();
	void OnClose();
	void OnReset();
	void OnUpdateClock(); 

public slots:

private slots:
	void OnBtnClick();

};
