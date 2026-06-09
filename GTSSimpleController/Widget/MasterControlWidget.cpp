#include "MasterControlWidget.h"
#include "GTSControllerWidget.h"
#include "../Mgr/TotalMgr.h"

#include <cmath>

CMasterControlWidget::CMasterControlWidget(QWidget* parent, CTotalMgr* mgr)
	: QWidget(parent)
	, m_pTotalMgr(mgr)
{
	ui.setupUi(this);
	m_pGTSControllerWidget = qobject_cast<GTSControllerWidget*>(parent);
	initMasterControlWidget();
	connectPrivateSignal();
}

CMasterControlWidget::~CMasterControlWidget()
{
}

// ===================================================================
void CMasterControlWidget::initMasterControlWidget()
{
	ui.spinBox_MotionVel->setValue(5.0);
	ui.doubleSpinBoxs_Acc->setValue(1.0);
	ui.doubleSpinBoxs_Dec->setValue(1.0);

	// ========== X 轴指示灯 ==========
	ui.radioButton_servoEnableX->setAutoExclusive(false);
	ui.radioButton_sevorAlarmX->setAutoExclusive(false);
	ui.radioButton_nLimitX->setAutoExclusive(false);
	ui.radioButton_pLimitX->setAutoExclusive(false);
	ui.radioButton_motionErrX->setAutoExclusive(false);
	ui.radioButton_motionStsX->setAutoExclusive(false);
	ui.radioButton_eStopX->setAutoExclusive(false);
	ui.radioButton_smoothStopX->setAutoExclusive(false);
	ui.radioButton_servoEnableX->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarmX->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimitX->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimitX->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErrX->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionStsX->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStopX->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStopX->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	// ========== Y 轴指示灯 ==========
	ui.radioButton_servoEnableY->setAutoExclusive(false);
	ui.radioButton_sevorAlarmY->setAutoExclusive(false);
	ui.radioButton_nLimitY->setAutoExclusive(false);
	ui.radioButton_pLimitY->setAutoExclusive(false);
	ui.radioButton_motionErrY->setAutoExclusive(false);
	ui.radioButton_motionStsY->setAutoExclusive(false);
	ui.radioButton_eStopY->setAutoExclusive(false);
	ui.radioButton_smoothStopY->setAutoExclusive(false);
	ui.radioButton_servoEnableY->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarmY->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimitY->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimitY->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErrY->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionStsY->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStopY->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStopY->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	// ========== Z 轴指示灯 ==========
	ui.radioButton_servoEnableZ->setAutoExclusive(false);
	ui.radioButton_sevorAlarmZ->setAutoExclusive(false);
	ui.radioButton_nLimitZ->setAutoExclusive(false);
	ui.radioButton_pLimitZ->setAutoExclusive(false);
	ui.radioButton_motionErrZ->setAutoExclusive(false);
	ui.radioButton_motionStsZ->setAutoExclusive(false);
	ui.radioButton_eStopZ->setAutoExclusive(false);
	ui.radioButton_smoothStopZ->setAutoExclusive(false);
	ui.radioButton_servoEnableZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarmZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimitZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimitZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErrZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionStsZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStopZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStopZ->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

// ===================================================================
void CMasterControlWidget::connectPrivateSignal()
{
	// ===== X 轴 Jog =====
	connect(ui.toolButton_xPlus, &QToolButton::pressed, this, [this]() { onJogPressed(1, 1); });
	connect(ui.toolButton_xPlus, &QToolButton::released, this, [this]() { onJogReleased(1); });
	connect(ui.toolButton_xMinus, &QToolButton::pressed, this, [this]() { onJogPressed(1, -1); });
	connect(ui.toolButton_xMinus, &QToolButton::released, this, [this]() { onJogReleased(1); });

	// ===== Y 轴 Jog =====
	connect(ui.toolButton_yPlus, &QToolButton::pressed, this, [this]() { onJogPressed(2, 1); });
	connect(ui.toolButton_yPlus, &QToolButton::released, this, [this]() { onJogReleased(2); });
	connect(ui.toolButton_yMinus, &QToolButton::pressed, this, [this]() { onJogPressed(2, -1); });
	connect(ui.toolButton_yMinus, &QToolButton::released, this, [this]() { onJogReleased(2); });

	// ===== Z 轴 Jog =====
	connect(ui.toolButton_zPlus, &QToolButton::pressed, this, [this]() { onJogPressed(3, 1); });
	connect(ui.toolButton_zPlus, &QToolButton::released, this, [this]() { onJogReleased(3); });
	connect(ui.toolButton_zMinus, &QToolButton::pressed, this, [this]() { onJogPressed(3, -1); });
	connect(ui.toolButton_zMinus, &QToolButton::released, this, [this]() { onJogReleased(3); });

	// ===== 点位运动启动 =====
	connect(ui.pushButton_ActMotion, &QPushButton::clicked,
		this, &CMasterControlWidget::onTrapMotion);

	
}

// ===================================================================
// onJogPressed / onJogReleased 保持不变
// ===================================================================
void CMasterControlWidget::onJogPressed(short axisId, int direction)
{
	if (!m_pTotalMgr) return;
	int index = axisId - 1;
	if (index < 0 || index >= (int)m_pTotalMgr->axisCount()) return;

	stuAxis* axis = m_pTotalMgr->getAxisRef(index);
	if (!axis) return;

	bool ok = m_pTotalMgr->motionMgr()->setAxisMotionMode(axisId, 1);
	if (!ok)
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 切换Jog模式失败").arg(axisName(axisId)), Qt::red);
		return;
	}

	stuJogParam jogParam;
	jogParam.dMotionVel = ui.spinBox_MotionVel->value();
	jogParam.acc = ui.doubleSpinBoxs_Acc->value();
	jogParam.dec = ui.doubleSpinBoxs_Dec->value();

	ok = m_pTotalMgr->motionMgr()->setJogParam(axisId, jogParam);
	if (!ok)
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 写入Jog参数失败").arg(axisName(axisId)), Qt::red);
		return;
	}

	ok = m_pTotalMgr->motionMgr()->startJogMotion(axisId, direction);
	if (ok)
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 %2Jog已启动")
			.arg(axisName(axisId))
			.arg(direction > 0 ? QStringLiteral("正向") : QStringLiteral("反向")),
			Qt::darkGreen);
	}
	else
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 Jog启动失败").arg(axisName(axisId)), Qt::red);
	}
}

void CMasterControlWidget::onJogReleased(short axisId)
{
	if (!m_pTotalMgr) return;
	bool ok = m_pTotalMgr->axisMgr()->stop(axisId, 1);
	if (ok)
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 Jog停止").arg(axisName(axisId)), Qt::darkGreen);
	}
	else
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 Jog停止失败").arg(axisName(axisId)), Qt::red);
	}
}

void CMasterControlWidget::onTrapMotion()
{
	if (!m_pTotalMgr) return;
	int axisCount = (int)m_pTotalMgr->axisCount();
	if (axisCount >= 1)
	{
		double targetX = ui.spinBox_curPosX->value();
		startSingleTrap(1, m_pTotalMgr->getAxisRef(0)->dCurPos, targetX);
	}
	if (axisCount >= 2)
	{
		double targetY = ui.spinBox_curPosY->value();
		startSingleTrap(2, m_pTotalMgr->getAxisRef(1)->dCurPos, targetY);
	}
}


bool CMasterControlWidget::startSingleTrap(short axisId, double curPos, double targetPos)
{
	double delta = targetPos - curPos;
	if (std::fabs(delta) < 1e-9)
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 已在目标位置，无需移动").arg(axisName(axisId)),
			Qt::darkGreen);
		return false;
	}

	// 拿到可写轴指针，填入本界面参数
	int index = axisId - 1;
	stuAxis* axis = m_pTotalMgr->getAxisRef(index);
	if (!axis) return false;

	axis->trapParam.dMotionVel = ui.spinBox_MotionVel->value();
	axis->trapParam.acc = ui.doubleSpinBoxs_Acc->value();
	axis->trapParam.dec = ui.doubleSpinBoxs_Dec->value();
	axis->trapParam.stepSize = static_cast<int>(delta);
	axis->trapParam.somoothTime = 0;
	axis->trapParam.cycleTimes = 0;
	axis->trapParam.Delay = 0;

	// 切换点位模式
	bool ok = m_pTotalMgr->motionMgr()->setAxisMotionMode(axisId, 0);
	if (!ok)
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 切换点位模式失败").arg(axisName(axisId)), Qt::red);
		return false;
	}

	// 启动 ———— 参考 AxisWidget::onTrapMotion
	ok = m_pTotalMgr->motionMgr()->startTrapMotion(axisId, axis->trapParam.stepSize);
	if (ok)
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 点位运动已启动  当前=%2 → 目标=%3  步数=%4  速度=%5  加速度=%6")
			.arg(axisName(axisId))
			.arg(curPos, 0, 'f', 3)
			.arg(targetPos, 0, 'f', 3)
			.arg(axis->trapParam.stepSize)
			.arg(axis->trapParam.dMotionVel)
			.arg(axis->trapParam.acc, 0, 'f', 3),
			Qt::darkGreen);
		return true;
	}
	else
	{
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 点位运动启动失败 err=%2")
			.arg(axisName(axisId))
			.arg(m_pTotalMgr->motionMgr()->lastError()),
			Qt::red);
		return false;
	}
}


QString CMasterControlWidget::axisName(short axisId)
{
	switch (axisId)
	{
	case 1: return QStringLiteral("X轴");
	case 2: return QStringLiteral("Y轴");
	case 3: return QStringLiteral("Z轴");
	default: return QStringLiteral("轴%1").arg(axisId);
	}
}


void CMasterControlWidget::onAxisUpdated(const std::vector<stuAxis>& axisInfo)
{
	m_bUpdatingFromBoard = true;

	auto updateOneAxis = [this](const stuAxis& axis,
		QRadioButton* servoEnable,
		QRadioButton* alarm,
		QRadioButton* nLimit,
		QRadioButton* pLimit,
		QRadioButton* motionErr,
		QRadioButton* motionSts,
		QRadioButton* eStop,
		QRadioButton* smoothStop,
		QLabel* actPosPluseData,
		QLabel* actVelPluseData,
		QLabel* actPluseAccData,
		QLabel* actPosData,
		QLabel* actVelData,
		QLabel* actAccData,
		QLabel* tgtPosData,
		QLabel* tgtVelData,
		QLabel* tgtAccData)
		{
			servoEnable->setChecked(axis.bServoOn);
			alarm->setChecked(axis.bAlarm);
			nLimit->setChecked(axis.bNegLimit);
			pLimit->setChecked(axis.bPosLimit);
			motionErr->setChecked(axis.bMError);
			motionSts->setChecked(axis.bMotion);
			eStop->setChecked(axis.bAbruptStop);
			smoothStop->setChecked(axis.bSmoothStop);

			actPosPluseData->setText(QString::number(axis.dCurPlusePos, 'f', 3));
			actVelPluseData->setText(QString::number(axis.dCurPluseVel, 'f', 3));
			actPluseAccData->setText(QString::number(axis.dCurPluseAcc, 'f', 3));

			actPosData->setText(QString::number(axis.dCurPos, 'f', 3));
			actVelData->setText(QString::number(axis.dCurVel, 'f', 3));
			actAccData->setText(QString::number(axis.dCurAcc, 'f', 3));

			tgtPosData->setText(QString::number(axis.dPrfPos, 'f', 3));
			tgtVelData->setText(QString::number(axis.dPrfVel, 'f', 3));
			tgtAccData->setText(QString::number(axis.dPrfAcc, 'f', 3));
		};

	if ((int)axisInfo.size() >= 1)
		updateOneAxis(axisInfo[0],
			ui.radioButton_servoEnableX,
			ui.radioButton_sevorAlarmX,
			ui.radioButton_nLimitX,
			ui.radioButton_pLimitX,
			ui.radioButton_motionErrX,
			ui.radioButton_motionStsX,
			ui.radioButton_eStopX,
			ui.radioButton_smoothStopX,
			ui.label_actPosPluseDataX,
			ui.label_actVelPluseDataX,
			ui.label_actPluseAccDataX,
			ui.label_actPosDataX,
			ui.label_actVelDataX,
			ui.label_actAccDataX,
			ui.label_tgtPosDataX,
			ui.label_tgtVelDataX,
			ui.label_tgtAccDataX);

	if ((int)axisInfo.size() >= 2)
		updateOneAxis(axisInfo[1],
			ui.radioButton_servoEnableY,
			ui.radioButton_sevorAlarmY,
			ui.radioButton_nLimitY,
			ui.radioButton_pLimitY,
			ui.radioButton_motionErrY,
			ui.radioButton_motionStsY,
			ui.radioButton_eStopY,
			ui.radioButton_smoothStopY,
			ui.label_actPosPluseDataY,
			ui.label_actVelPluseDataY,
			ui.label_actPluseAccDataY,
			ui.label_actPosDataY,
			ui.label_actVelDataY,
			ui.label_actAccDataY,
			ui.label_tgtPosDataY,
			ui.label_tgtVelDataY,
			ui.label_tgtAccDataY);

	if ((int)axisInfo.size() >= 3)
		updateOneAxis(axisInfo[2],
			ui.radioButton_servoEnableZ,
			ui.radioButton_sevorAlarmZ,
			ui.radioButton_nLimitZ,
			ui.radioButton_pLimitZ,
			ui.radioButton_motionErrZ,
			ui.radioButton_motionStsZ,
			ui.radioButton_eStopZ,
			ui.radioButton_smoothStopZ,
			ui.label_actPosPluseDataZ,
			ui.label_actVelPluseDataZ,
			ui.label_actPluseAccDataZ,
			ui.label_actPosDataZ,
			ui.label_actVelDataZ,
			ui.label_actAccDataZ,
			ui.label_tgtPosDataZ,
			ui.label_tgtVelDataZ,
			ui.label_tgtAccDataZ);

	// ===== lineEdit 显示当前位置 =====
	if ((int)axisInfo.size() >= 1 && !ui.spinBox_curPosX->hasFocus())
		ui.spinBox_curPosX->setValue(static_cast<int>(axisInfo[0].dCurPos));
	if ((int)axisInfo.size() >= 2 && !ui.spinBox_curPosY->hasFocus())
		ui.spinBox_curPosY->setValue(static_cast<int>(axisInfo[1].dCurPos));

	m_bUpdatingFromBoard = false;
}

void CMasterControlWidget::onAxisParamUpdated(const std::vector<stuAxis>& axisInfo)
{
	Q_UNUSED(axisInfo);
}
