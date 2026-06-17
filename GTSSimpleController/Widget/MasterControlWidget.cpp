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


void CMasterControlWidget::initMasterControlWidget()
{
	ui.spinBox_MotionVel->setValue(5.0);
	ui.doubleSpinBoxs_Acc->setValue(1.0);
	ui.doubleSpinBoxs_Dec->setValue(1.0);

	ui.radioButton_servoEnable1->setAutoExclusive(false);
	ui.radioButton_sevorAlarm1->setAutoExclusive(false);
	ui.radioButton_nLimit1->setAutoExclusive(false);
	ui.radioButton_pLimit1->setAutoExclusive(false);
	ui.radioButton_motionErr1->setAutoExclusive(false);
	ui.radioButton_motionSts1->setAutoExclusive(false);
	ui.radioButton_eStop1->setAutoExclusive(false);
	ui.radioButton_smoothStop1->setAutoExclusive(false);
	ui.radioButton_servoEnable1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarm1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimit1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimit1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErr1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionSts1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStop1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStop1->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	ui.radioButton_servoEnable2->setAutoExclusive(false);
	ui.radioButton_sevorAlarm2->setAutoExclusive(false);
	ui.radioButton_nLimit2->setAutoExclusive(false);
	ui.radioButton_pLimit2->setAutoExclusive(false);
	ui.radioButton_motionErr2->setAutoExclusive(false);
	ui.radioButton_motionSts2->setAutoExclusive(false);
	ui.radioButton_eStop2->setAutoExclusive(false);
	ui.radioButton_smoothStop2->setAutoExclusive(false);
	ui.radioButton_servoEnable2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarm2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimit2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimit2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErr2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionSts2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStop2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStop2->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	ui.radioButton_servoEnable3->setAutoExclusive(false);
	ui.radioButton_sevorAlarm3->setAutoExclusive(false);
	ui.radioButton_nLimit3->setAutoExclusive(false);
	ui.radioButton_pLimit3->setAutoExclusive(false);
	ui.radioButton_motionErr3->setAutoExclusive(false);
	ui.radioButton_motionSts3->setAutoExclusive(false);
	ui.radioButton_eStop3->setAutoExclusive(false);
	ui.radioButton_smoothStop3->setAutoExclusive(false);
	ui.radioButton_servoEnable3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarm3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimit3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimit3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErr3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionSts3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStop3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStop3->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	ui.radioButton_servoEnable4->setAutoExclusive(false);
	ui.radioButton_sevorAlarm4->setAutoExclusive(false);
	ui.radioButton_nLimit4->setAutoExclusive(false);
	ui.radioButton_pLimit4->setAutoExclusive(false);
	ui.radioButton_motionErr4->setAutoExclusive(false);
	ui.radioButton_motionSts4->setAutoExclusive(false);
	ui.radioButton_eStop4->setAutoExclusive(false);
	ui.radioButton_smoothStop4->setAutoExclusive(false);
	ui.radioButton_servoEnable4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarm4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimit4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimit4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErr4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionSts4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStop4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStop4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void CMasterControlWidget::connectPrivateSignal()
{
	connect(ui.toolButton_Plus1, &QToolButton::pressed, this, [this]() { onJogPressed(1, 1); });
	connect(ui.toolButton_Plus1, &QToolButton::released, this, [this]() { onJogReleased(1); });
	connect(ui.toolButton_Minus1, &QToolButton::pressed, this, [this]() { onJogPressed(1, -1); });
	connect(ui.toolButton_Minus1, &QToolButton::released, this, [this]() { onJogReleased(1); });
	connect(ui.toolButton_Plus2, &QToolButton::pressed, this, [this]() { onJogPressed(2, 1); });
	connect(ui.toolButton_Plus2, &QToolButton::released, this, [this]() { onJogReleased(2); });
	connect(ui.toolButton_Minus2, &QToolButton::pressed, this, [this]() { onJogPressed(2, -1); });
	connect(ui.toolButton_Minus2, &QToolButton::released, this, [this]() { onJogReleased(2); });
	connect(ui.toolButton_Plus3, &QToolButton::pressed, this, [this]() { onJogPressed(3, 1); });
	connect(ui.toolButton_Plus3, &QToolButton::released, this, [this]() { onJogReleased(3); });
	connect(ui.toolButton_Minus3, &QToolButton::pressed, this, [this]() { onJogPressed(3, -1); });
	connect(ui.toolButton_Minus3, &QToolButton::released, this, [this]() { onJogReleased(3); });
	connect(ui.toolButton_Plus4, &QToolButton::pressed, this, [this]() { onJogPressed(4, 1); });
	connect(ui.toolButton_Plus4, &QToolButton::released, this, [this]() { onJogReleased(4); });
	connect(ui.toolButton_Minus4, &QToolButton::pressed, this, [this]() { onJogPressed(4, -1); });
	connect(ui.toolButton_Minus4, &QToolButton::released, this, [this]() { onJogReleased(4); });
	connect(ui.pushButton_ActMotion, &QPushButton::clicked, this, &CMasterControlWidget::onTrapMotion);
	// 回零按钮
	connect(ui.pushButtonHome1, &QPushButton::clicked, this, [this]() { onHomeButtonClicked(1); });
	connect(ui.pushButtonHome2, &QPushButton::clicked, this, [this]() { onHomeButtonClicked(2); });
	connect(ui.pushButtonHome3, &QPushButton::clicked, this, [this]() { onHomeButtonClicked(3); });
	connect(ui.pushButtonHome4, &QPushButton::clicked, this, [this]() { onHomeButtonClicked(4); });
}

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
	double target1 = ui.spinBox_curPos1->value();
	startSingleTrap(1, m_pTotalMgr->getAxisRef(0)->dEncPos, target1);
	double target2 = ui.spinBox_curPos2->value();
	startSingleTrap(2, m_pTotalMgr->getAxisRef(1)->dEncPos, target2);
	double target3 = ui.spinBox_curPos3->value();
	startSingleTrap(3, m_pTotalMgr->getAxisRef(2)->dEncPos, target3);
	double target4 = ui.spinBox_curPos4->value();
	startSingleTrap(4, m_pTotalMgr->getAxisRef(3)->dEncPos, target4);
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

	// 启动
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

void CMasterControlWidget::onHomeButtonClicked(short axis)
{
	if (!m_pTotalMgr || !m_pGTSControllerWidget) return;
	auto axisMgr = m_pTotalMgr->axisMgr();
	if (!axisMgr) return;

	double vel = static_cast<double>(ui.spinBox_MotionVel->value());
	double acc = ui.doubleSpinBoxs_Acc->value();

	// 参数保护:确保速度/加速度为正
	if (vel <= 0.0 || acc <= 0.0) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("回零参数错误：速度=%1 加速度=%2（必须大于0）").arg(vel).arg(acc),
			Qt::red);
		return;
	}


	bool ok = axisMgr->home(axis, 200000, vel, acc, 1000);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 回零已启动").arg(axisName(axis)), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("%1 回零失败 err=%2").arg(axisName(axis)).arg(axisMgr->lastError()),
			Qt::red);
	}
}




QString CMasterControlWidget::axisName(short axisId)
{
	switch (axisId)
	{
	case 1: return QStringLiteral("轴1");
	case 2: return QStringLiteral("轴2");
	case 3: return QStringLiteral("轴3");
	case 4: return QStringLiteral("轴4");
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
		QLabel* actPosData,
		QLabel* actVelData,
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

			actPosPluseData->setText(QString::number(axis.dEncPos, 'f', 3));
			actVelPluseData->setText(QString::number(axis.dEncVel, 'f', 3));

			actPosData->setText(QString::number(axis.dEncPosMm, 'f', 3));
			actVelData->setText(QString::number(axis.dEncVelMm, 'f', 3));

			tgtPosData->setText(QString::number(axis.dPrfPos, 'f', 3));
			tgtVelData->setText(QString::number(axis.dPrfVel, 'f', 3));
			tgtAccData->setText(QString::number(axis.dPrfAcc, 'f', 3));
		};

	if ((int)axisInfo.size() >= 1)
		updateOneAxis(axisInfo[0],
			ui.radioButton_servoEnable1,
			ui.radioButton_sevorAlarm1,
			ui.radioButton_nLimit1,
			ui.radioButton_pLimit1,
			ui.radioButton_motionErr1,
			ui.radioButton_motionSts1,
			ui.radioButton_eStop1,
			ui.radioButton_smoothStop1,
			ui.label_actPosPluseData1,
			ui.label_actVelPluseData1,
			ui.label_actPosData1,
			ui.label_actVelData1,
			ui.label_tgtPosData1,
			ui.label_tgtVelData1,
			ui.label_tgtAccData1);

	if ((int)axisInfo.size() >= 2)
		updateOneAxis(axisInfo[1],
			ui.radioButton_servoEnable2,
			ui.radioButton_sevorAlarm2,
			ui.radioButton_nLimit2,
			ui.radioButton_pLimit2,
			ui.radioButton_motionErr2,
			ui.radioButton_motionSts2,
			ui.radioButton_eStop2,
			ui.radioButton_smoothStop2,
			ui.label_actPosPluseData2,
			ui.label_actVelPluseData2,
			ui.label_actPosData2,
			ui.label_actVelData2,
			ui.label_tgtPosData2,
			ui.label_tgtVelData2,
			ui.label_tgtAccData2);

	if ((int)axisInfo.size() >= 3)
		updateOneAxis(axisInfo[2],
			ui.radioButton_servoEnable3,
			ui.radioButton_sevorAlarm3,
			ui.radioButton_nLimit3,
			ui.radioButton_pLimit3,
			ui.radioButton_motionErr3,
			ui.radioButton_motionSts3,
			ui.radioButton_eStop3,
			ui.radioButton_smoothStop3,
			ui.label_actPosPluseData3,
			ui.label_actVelPluseData3,
			ui.label_actPosData3,
			ui.label_actVelData3,
			ui.label_tgtPosData3,
			ui.label_tgtVelData3,
			ui.label_tgtAccData3);

	if ((int)axisInfo.size() >= 4)
		updateOneAxis(axisInfo[3],
			ui.radioButton_servoEnable4,
			ui.radioButton_sevorAlarm4,
			ui.radioButton_nLimit4,
			ui.radioButton_pLimit4,
			ui.radioButton_motionErr4,
			ui.radioButton_motionSts4,
			ui.radioButton_eStop4,
			ui.radioButton_smoothStop4,
			ui.label_actPosPluseData4,
			ui.label_actVelPluseData4,
			ui.label_actPosData4,
			ui.label_actVelData4,
			ui.label_tgtPosData4,
			ui.label_tgtVelData4,
			ui.label_tgtAccData4);

	if ((int)axisInfo.size() >= 1 && !ui.spinBox_curPos1->hasFocus())
		ui.spinBox_curPos1->setValue(static_cast<int>(axisInfo[0].dEncPos));
	if ((int)axisInfo.size() >= 2 && !ui.spinBox_curPos2->hasFocus())
		ui.spinBox_curPos2->setValue(static_cast<int>(axisInfo[1].dEncPos));
	if ((int)axisInfo.size() >= 3 && !ui.spinBox_curPos3->hasFocus())
		ui.spinBox_curPos3->setValue(static_cast<int>(axisInfo[2].dEncPos));
	if ((int)axisInfo.size() >= 4 && !ui.spinBox_curPos4->hasFocus())
		ui.spinBox_curPos4->setValue(static_cast<int>(axisInfo[3].dEncPos));

	m_bUpdatingFromBoard = false;
}

void CMasterControlWidget::onAxisParamUpdated(const std::vector<stuAxis>& axisInfo)
{
	Q_UNUSED(axisInfo);
}
