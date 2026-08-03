#pragma once

#include <QWidget>
#include "ui_MasterControlWidget.h"
#include "../../GtsCore/GtsAxisMgr.h"

class GtsMgr;
class GTSControllerWidget;

class CMasterControlWidget : public QWidget
{
	Q_OBJECT

public:
	CMasterControlWidget(QWidget* parent = nullptr, GtsMgr* mgr = nullptr);
	~CMasterControlWidget();

public slots:
	void onAxisUpdated(const std::vector<SingleAxisInfo>& axisInfo);
	void onAxisParamUpdated(const std::vector<SingleAxisInfo>& axisInfo);

private:
	Ui::CMasterControlWidgetClass ui;
	GtsMgr* m_pTotalMgr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;
	bool m_bUpdatingFromBoard = false;

private:
	void initMasterControlWidget();
	void connectPrivateSignal();

	// Jog 运动
	void onJogPressed(short axisId, int direction);
	void onJogReleased(short axisId);

	// 点位运动
	void onTrapMotion();
	bool startSingleTrap(short axisId, double stepMm);

	void onHomeButtonClicked(short axis);
	void onStopAll();


	// 硬绑定：轴号 → 名称
	static QString axisName(short axisId);
};
