#pragma once

#include <QMainWindow>
#include "ui_ConfigWidget.h"

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

private:
	void InitConfigWidget();
	void InitUI();
	void connectSignalsAndSlots();
	void refreshAlarmButton();
	void refreshLimitButton();
	void onLimitEnable();
	void refreshScaleEquivalents();   
	void onProfileScaleChanged(); 
	void onEncoderScaleChanged();
	void onPulseOutputModeChanged(int index);
	void refreshDacValues();
	void onDacBiasChanged();
	void onDacLimitChanged();
	void onInputPulseInvertChanged(int index);
	void onPulseCountSourceChanged(int index);
	void refreshFollowErrorLimit();
	void onFollowErrorLimitChanged();
	void refreshStopDecel();
	void onStopDecelChanged();
	void onLimitSwitchLevelChanged(int index);
	void refreshAxisCtrlMode();
	void onAxisCtrlModeChanged(int index);
	void refreshStopIO();
	void onSmoothStopIOChanged();
	void onEStopIOChanged();
	void refreshGpiSense();
	void onGpiSenseChanged();
	// 下载配置文件到板卡
	void onLoadToBoard();
	// 伺服报警
	void onservoAlarmEnable();

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