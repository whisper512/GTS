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
	
	// 更新标志位
	bool m_bUpdatingFromBoard = false;
	short m_iAxisId = 1; 

	void initWidget();
	void connectPrivateSignal();

	// 清除状态
	void onClearState();
	// 伺服使能
	void onServoOn();
	// 伺服关闭
	void onServoOff();
	// 清空位置
	void onClearPos();
	// 平滑停止
	void onSmoothStop();
	// 紧急停止
	void onEStop();
	// 点位运动开始
	void onTrapMotion();

public slots:
	// 更新轴实时信息
	void onAxisUpdated(const std::vector<stuAxis>& axisInfo);
	// 更新轴点位参数
	void onAxisTrapParamUpdated(const std::vector<stuAxis>& axisInfo);
private slots:
	void onBtnClick();
	void onTrapParamChanged();
	void onComboBoxCurrentIndexChanged(int index);
};
