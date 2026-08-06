#pragma once

#include <QWidget>
#include "ui_MasterControlWidget.h"
#include "../../GtsCore/GtsAxisMgr.h"
#include "../../GtsCore/ControllerData.h"

class GtsMgr;

class MasterControlWidget : public QWidget
{
	Q_OBJECT

public:
	MasterControlWidget(QWidget* parent = nullptr);
	~MasterControlWidget();
	void setGtsTotalMgr(GtsMgr* mgr);

private:
	Ui::CMasterControlWidgetClass ui;
	GtsMgr* m_gtsMgr = nullptr;
	short m_axisId = 1;
	bool m_connectionsInitialized = false;

	void initConnections();
	short axisIdByName(AxisName name) const;

	void onJogPressed(short axisId, int direction);
	void onJogReleased(short axisId);
	void onStopAll();
	void onHome(short axisId);
	void onActMotion();

public slots:
	void onAxisUpdated(const std::vector<SingleAxisInfo>& axisInfo);
};
