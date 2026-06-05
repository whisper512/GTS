#pragma once

#include <QMainWindow>
#include "ui_AdvConfigWidget.h"

class CTotalMgr;
class GTSControllerWidget;

class CConfigWidget : public QMainWindow
{
	Q_OBJECT

public:
	CConfigWidget(QWidget *parent = nullptr, CTotalMgr* mgr = nullptr);
	~CConfigWidget();

private:
	Ui::CConfigWidgetClass ui;
	CTotalMgr* m_pTotalMgr = nullptr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;
	bool m_bRefreshing = false;

private:
	void InitConfigWidget();
	void InitUI();
	void connectSignalsAndSlots();
	// axis
	void onservoAlarmEnable();
	void onLimitEnable();
	void onProfileScaleChanged(); 
	void onEncoderScaleChanged();
	void onSmoothStopIOChanged();
	void onEStopIOChanged();
	void onLimitSwitchLevelChanged(int index);
	void onAxisCtrlModeChanged(int index);
	// step
	void onPulseOutputModeChanged(int index);
	// encoder
	void onInputPulseInvertChanged(int index);
	void onPulseCountSourceChanged(int index);
	//dac
	void onDacBiasChanged();
	void onDacLimitChanged();
	// control
	void onFollowErrorLimitChanged();
	// profile
	void onStopDecelChanged();
	// di
	void onGpiSenseChanged();
	void onLoadToBoard();

	//axxis
	void refreshAlarmButton();
	void refreshLimitButton();
	void refreshAxisCtrlMode();
	void refreshScaleEquivalents();
	// step
	void refreshStepPulseMode();
	// encoder
	void refreshEncoderConfig();

	void refreshDacValues();
	void refreshFollowErrorLimit();
	void refreshStopDecel();
	void refreshGpiSense();
	void refreshStopIO();

signals:

private slots:
	void onBtnClicked();

public slots:
	void onAlarmStateChanged();

};

// 给 QComboBox 添加一组数字
inline void ComboAddNumbers(QComboBox* cb, int n)
{
	if (!cb) return;
	for (int i = 1; i <= n; ++i) {
		cb->addItem(QString::number(i));
	}
}
// 给 QComboBox 添加一组字符串
inline void ComboAddItems(QComboBox* cb, std::initializer_list<QString> items)
{
	if (!cb) return;
	for (const auto& s : items) {
		cb->addItem(s);
	}
}