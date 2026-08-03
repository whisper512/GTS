#pragma once
#include <QWidget>
#include "../../GtsCore/GtsMgr.h"
#include "ui_AxisWidget.h"

class GtsMgr;

class CAxisWidget : public QWidget
{
	Q_OBJECT

public:
	CAxisWidget(QWidget* parent = nullptr);
	~CAxisWidget();
	void setGtsTotalMgr(GtsMgr* mgr);

private:
	Ui::CAxisWidgetClass ui;
	GtsMgr* m_gtsMgr = nullptr;

	bool  m_updatingFromBoard = false;
	short m_axisId = 1;
	short m_axisMode = 0;

	void initWidget();
	void initConnections();
	void connectAxisSignals();
	void updateUIEnable(int index);

	// Axis operations
	void onClearState();
	void onServoOn();
	void onServoOff();
	void onClearPos();
	void onSmoothStop();
	void onEStop();
	void onTrapMotion();
	void onJogPressed(int direction);   // direction: +1 positive, -1 negative
	void onJogReleased();

public slots:
	void onAxisUpdated(const std::vector<SingleAxisInfo>& axisInfo);
	void onAxisSettingUpdated(const std::vector<SingleAxisInfo>& axisInfo);

private slots:
	void onBtnClick();
	void onTrapParamChanged();
	void onJogParamChanged();
	void onComboBoxCurrentIndexChanged(int index);
	void onComboBoxModeCurrentIndexChanged(int index);
};
