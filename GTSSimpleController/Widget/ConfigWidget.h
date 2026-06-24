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
	bool m_bRefreshing = false;

private:
	void InitConfigWidget();
	void InitUI();
	void connectSignalsAndSlots();
	void onLoadToBoard();

	//dac参数
	void onDacBiasChanged();
	void onDacLimitChanged();
	// 控制器参数
	void onFollowErrorLimitChanged();
	// 规划期参数
	void onStopDecelChanged();
	
	// 刷新
	void refreshDacValues();
	void refreshFollowErrorLimit();
	void refreshStopDecel();
	void refreshGpiSense();
	void refreshScaleValues();
	void onPrfAlphaChanged();
	void onPrfBetaChanged();
	void onEncAlphaChanged();
	void onEncBetaChanged();

	// 控制模式
	void refreshControlMode();
	void onControlModeChanged();

	// 回零参数
	void refreshHomeConfig();
	void onHomeModeChanged();
	void onHomeVelChanged();
	void onHomeAccChanged();
	void onHomeRangeChanged();
	void onHomeOffsetChanged();

	// 轴限位
	void refreshAxisLimit();
	void onPosLimitChanged();
	void onNegLimitChanged();

signals:

private slots:
	void onBtnClicked();

public slots:
	void onconfigChanged();

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