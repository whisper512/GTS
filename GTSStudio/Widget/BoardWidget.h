#pragma once
#include <QWidget>
#include "../../GtsCore/GtsBoardMgr.h"
#include "ui_BoradWidget.h"

class GtsMgr;

class BoardWidget : public QWidget 
{
	Q_OBJECT

public:
	BoardWidget(QWidget* parent = nullptr);
	~BoardWidget();
	void setGtsTotalMgr(GtsMgr* mgr);

private:
	Ui::BoardWidgetClass ui;
	GtsMgr* m_gtsMgr = nullptr;

	void initConnections();
	void updateBoardState(bool isOpen);
	void onOpen();
	void onClose();
	void onReset();

signals:


public slots:
	void onBoardClockUpdated(const Clock& clock);
private slots:
	void onBtnClick();

};
