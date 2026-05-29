#pragma once
#include <QWidget>
#include <AxisMgr.h>
#include "ui_AxisWidget.h"

class CTotalMgr;
class GTSControllerWidget;

class CAxisWidget : public QWidget
{
	Q_OBJECT

public:
	CAxisWidget(QWidget* parent = nullptr, CTotalMgr* mgr = nullptr);
	~CAxisWidget();

private:
	Ui::CAxisWidgetClass ui;
	CTotalMgr* m_pTotalMgr = nullptr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;

	bool m_bUpdatingFromBoard = false;
	short m_iAxisId = 1; 

	void initWidget();
	void connectPrivateSignal();

	void onClearState();
	void onServoOn();
	void onServoOff();
	void onClearPos();
	void onSmoothStop();
	void onEStop();
	void onActMotion();

public slots:
	void onAxisUpdated(const std::vector<stuAxis>& axisInfo);
	void onAxisTrapParamUpdated(const std::vector<stuAxis>& axisInfo);
private slots:
	void onBtnClick();
	void onTrapParamChanged();
	void onComboBoxCurrentIndexChanged(int index);
};
