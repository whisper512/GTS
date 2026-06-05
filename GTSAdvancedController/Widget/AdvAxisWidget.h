#pragma once
#include <QWidget>
#include "../Mgr/AdvAxisMgr.h"
#include "ui_AdvAxisWidget.h"

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
	short m_iAxisMode = 0;

	void initWidget();
	void connectPrivateSignal();
	void updateUIEnable(int index);

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
	void onJogPressed(int direction);   // direction: +1 正向, -1 反向
	void onJogReleased();

public slots:
	// 更新轴实时信息
	void onAxisUpdated(const std::vector<stuAxis>& axisInfo);
	// 更新轴通用信息
	void onAxisParamUpdated(const std::vector<stuAxis>& axisInfo);

private slots:
	void onBtnClick();
	void onTrapParamChanged();
	void onJogParamChanged();
	void onComboBoxCurrentIndexChanged(int index);
	void onComboBoxModeCurrentIndexChanged(int index);
};
