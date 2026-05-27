#pragma once
#include <QWidget>
#include <QTimer>
#include "ui_AxisWidget.h"

class CTotalMgr;
class GTSControllerWidget;

class CAxisWidget : public QWidget
{
	Q_OBJECT

public:
	CAxisWidget(QWidget* parent = nullptr, CTotalMgr* mgr = nullptr);
	~CAxisWidget();

	void startRefresh();
	void stopRefresh();

private:
	Ui::CAxisWidgetClass ui;
	QTimer* m_pClockTimer = nullptr;
	CTotalMgr* m_pTotalMgr = nullptr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;

	int m_iAxisIndex = 1;     
	short m_iAxisId = 0; 

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
