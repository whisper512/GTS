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

	void connectPrivateSignal();
	void updateBoardState(bool isOpen);
	void onOpen();
	void onClose();
	void onReset();
	void onUpdateClock(); 

public slots:

private slots:
	void onBtnClick();

};
