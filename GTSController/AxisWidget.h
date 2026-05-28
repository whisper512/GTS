#pragma once
#include <QWidget>
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

	short m_iAxisId = 1; 

	void initWidget();
	void connectPrivateSignal();
	void onUpdateAxisInfo();

	void onClearState();
	void onServoOn();
	void onServoOff();
	void onClearPos();
	void onSmoothStop();
	void onEStop();
	void onActMotion();

public slots:
	
private slots:
	void onBtnClick();
	void onComboBoxCurrentIndexChanged(int index);
};
