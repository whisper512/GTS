#pragma once
#include <QWidget>
#include "../../GtsCore/GtsBoardMgr.h"
#include "ui_BoradWidget.h"

class GtsMgr;
class GTSControllerWidget;

class CBoardWidget : public QWidget 
{
	Q_OBJECT

public:
	CBoardWidget(QWidget* parent = nullptr, GtsMgr* mgr = nullptr);
	~CBoardWidget();

private:
	Ui::BoardWidgetClass ui;
	GtsMgr* m_pTotalMgr = nullptr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;

	void connectPrivateSignal();
	void upUIdateBoardState(bool isOpen);
	void onOpen();
	void onClose();
	void onReset();

signals:


public slots:
	void onBoardClockUpdated(const Clock& clock);
private slots:
	void onBtnClick();

};
