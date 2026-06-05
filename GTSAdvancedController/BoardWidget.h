#pragma once
#include <QWidget>
#include "BoardMgr.h"
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
	CTotalMgr* m_pTotalMgr = nullptr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;

	void connectPrivateSignal();
	void upUIdateBoardState(bool isOpen);
	void onOpen();
	void onClose();
	void onReset();

signals:


public slots:
	void onBoardClockUpdated(const stuClock& clock);
private slots:
	void onBtnClick();

};
