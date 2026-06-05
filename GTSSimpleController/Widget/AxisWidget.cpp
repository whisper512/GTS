#include "AxisWidget.h"
#include "GTSControllerWidget.h"
#include "../Mgr/TotalMgr.h"
#include "../Mgr/BoardMgr.h"
#include "../Mgr/AxisMgr.h"

#include <QMessageBox>

CAxisWidget::CAxisWidget(QWidget* parent, CTotalMgr* mgr)
	: QWidget(parent)
	, m_pTotalMgr(mgr)
{
	ui.setupUi(this);
	m_pGTSControllerWidget = qobject_cast<GTSControllerWidget*>(parent);
	initWidget();
	connectPrivateSignal();
}

CAxisWidget::~CAxisWidget()
{
}


void CAxisWidget::initWidget()
{
	ui.comboBox_axisID->addItem(QStringLiteral("轴 1"));
	ui.comboBox_axisID->addItem(QStringLiteral("轴 2"));
	ui.comboBox_axisID->addItem(QStringLiteral("轴 3"));
	ui.comboBox_axisID->addItem(QStringLiteral("轴 4"));

	ui.comboBox_Mode->addItem(QStringLiteral("点位运动(trap)"));
    ui.comboBox_Mode->addItem(QStringLiteral("Jog运动"));

	// radiobtn禁用互斥
	ui.radioButton_servoEnable->setAutoExclusive(false);
	ui.radioButton_sevorAlarm->setAutoExclusive(false);
	ui.radioButton_nLimit->setAutoExclusive(false);
	ui.radioButton_pLimit->setAutoExclusive(false);
	ui.radioButton_motionErr->setAutoExclusive(false);
	ui.radioButton_motionSts->setAutoExclusive(false);
	ui.radioButton_eStop->setAutoExclusive(false);
	ui.radioButton_smoothStop->setAutoExclusive(false);
	// 禁止用户点击
	ui.radioButton_servoEnable->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_sevorAlarm->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_nLimit->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_pLimit->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionErr->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_motionSts->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_eStop->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui.radioButton_smoothStop->setAttribute(Qt::WA_TransparentForMouseEvents, true);

}

void CAxisWidget::connectPrivateSignal()
{
	connect(ui.comboBox_axisID, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CAxisWidget::onComboBoxCurrentIndexChanged);
	connect(ui.comboBox_Mode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CAxisWidget::onComboBoxModeCurrentIndexChanged);

	connect(ui.pushButton_clearState, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_sevorOn, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_clearPos, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_smoothStop, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_eStop, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_TarpActMotion, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_jogPMotion, &QPushButton::pressed, this, [this]() { onJogPressed(1); });
	connect(ui.pushButton_jogPMotion, &QPushButton::released, this, [this]() { onJogReleased(); });
	connect(ui.pushButton_jogNMotion, &QPushButton::pressed, this, [this]() { onJogPressed(-1); });
	connect(ui.pushButton_jogNMotion, &QPushButton::released, this, [this]() { onJogReleased(); });

	connect(ui.spinBox_trapMotionVel, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
	connect(ui.doubleSpinBoxs_trapAcc, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
	connect(ui.doubleSpinBoxs_trapDec, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_trapStepSize, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_trapSmoothTime, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_trapCycleTime, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_TrapInPositionDelay, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);

	connect(ui.doubleSpinBoxs_jogAcc, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onJogParamChanged);
	connect(ui.doubleSpinBoxs_jogDec, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onJogParamChanged);
}

void CAxisWidget::updateUIEnable(int index)
{
	if (index == 0)
	{
		// 点位运动
		ui.spinBox_jogMotionVel->setEnabled(false);
		ui.doubleSpinBoxs_jogAcc->setEnabled(false);
        ui.doubleSpinBoxs_jogDec->setEnabled(false);
		ui.pushButton_jogPMotion->setEnabled(false);
        ui.pushButton_jogNMotion->setEnabled(false);

		ui.spinBox_trapMotionVel->setEnabled(true);
		ui.doubleSpinBoxs_trapAcc->setEnabled(true);
		ui.doubleSpinBoxs_trapDec->setEnabled(true);
		ui.spinBox_trapStepSize->setEnabled(true);
		ui.spinBox_trapSmoothTime->setEnabled(true);
		ui.spinBox_trapCycleTime->setEnabled(true);
		ui.spinBox_TrapInPositionDelay->setEnabled(true);
		ui.pushButton_TarpActMotion->setEnabled(true);
	}
	else if (index == 1)
	{
		// jog运动
		ui.spinBox_jogMotionVel->setEnabled(true);
		ui.doubleSpinBoxs_jogAcc->setEnabled(true);
		ui.doubleSpinBoxs_jogDec->setEnabled(true);
		ui.pushButton_jogPMotion->setEnabled(true);
		ui.pushButton_jogNMotion->setEnabled(true);

		ui.spinBox_trapMotionVel->setEnabled(false);
		ui.pushButton_TarpActMotion->setEnabled(false);
		ui.doubleSpinBoxs_trapAcc->setEnabled(false);
		ui.doubleSpinBoxs_trapDec->setEnabled(false);
		ui.spinBox_trapStepSize->setEnabled(false);
		ui.spinBox_trapSmoothTime->setEnabled(false);
		ui.spinBox_trapCycleTime->setEnabled(false);
		ui.spinBox_TrapInPositionDelay->setEnabled(false);
        ui.pushButton_TarpActMotion->setEnabled(false);
	}
}


void CAxisWidget::onBtnClick()
{
	if (!m_pTotalMgr) return;
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;

	QString objName = btn->objectName();
	if (objName == "pushButton_clearState") {
		onClearState();
	}
	else if (objName == "pushButton_sevorOn") {
		if (ui.pushButton_sevorOn->text() == QStringLiteral("使能")) {
			onServoOn();
		}
		else
		{
			onServoOff();
		}
	}
	else if (objName == "pushButton_clearPos") {
		onClearPos();
	}
	else if (objName == "pushButton_smoothStop") {
		onSmoothStop();
	}
	else if (objName == "pushButton_eStop") {
		onEStop();
	}
	else if (objName == "pushButton_TarpActMotion") {
		onTrapMotion();
	}
}

void CAxisWidget::onAxisParamUpdated(const std::vector<stuAxis>& axisInfo)
{
	m_bUpdatingFromBoard = true;
    int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)axisInfo.size()) return;
	const stuAxis& axis = axisInfo[index];

	ui.comboBox_Mode->setCurrentIndex(axis.lPrfMode);
	ui.spinBox_trapMotionVel->setValue((int)axis.trapParam.dMotionVel);
	ui.spinBox_trapStepSize->setValue(axis.trapParam.stepSize);
	ui.doubleSpinBoxs_trapAcc->setValue(axis.trapParam.acc);
    ui.doubleSpinBoxs_trapDec->setValue(axis.trapParam.dec);
    ui.spinBox_trapSmoothTime->setValue(axis.trapParam.somoothTime);
	ui.spinBox_trapCycleTime->setValue(axis.trapParam.cycleTimes);
    ui.spinBox_TrapInPositionDelay->setValue(axis.trapParam.Delay);
	ui.spinBox_jogMotionVel->setValue(axis.jogParam.dMotionVel);
	ui.doubleSpinBoxs_jogAcc->setValue(axis.jogParam.acc);
    ui.doubleSpinBoxs_jogDec->setValue(axis.jogParam.dec);

	updateUIEnable(ui.comboBox_Mode->currentIndex());
	m_bUpdatingFromBoard = false;
}


void CAxisWidget::onTrapParamChanged()
{
	if (m_bUpdatingFromBoard) return;
	if (!m_pTotalMgr) return;
	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)m_pTotalMgr->axisCount()) return;
	stuAxis* axis = m_pTotalMgr->getAxisRef(index);
    if (!axis) return;
    axis->trapParam.dMotionVel = ui.spinBox_trapMotionVel->value();
	axis->trapParam.acc = ui.doubleSpinBoxs_trapAcc->value();
	axis->trapParam.dec = ui.doubleSpinBoxs_trapDec->value();
	axis->trapParam.stepSize = ui.spinBox_trapStepSize->value();
	axis->trapParam.somoothTime = ui.spinBox_trapSmoothTime->value();
	axis->trapParam.cycleTimes = ui.spinBox_trapCycleTime->value();
	axis->trapParam.Delay = ui.spinBox_TrapInPositionDelay->value();
}

void CAxisWidget::onJogParamChanged()
{
	if (m_bUpdatingFromBoard) return;
	if (!m_pTotalMgr) return;
	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)m_pTotalMgr->axisCount()) return;
	stuAxis* axis = m_pTotalMgr->getAxisRef(index);
	if (!axis) return;
    axis->jogParam.dMotionVel = ui.spinBox_jogMotionVel->value();
    axis->jogParam.acc = ui.doubleSpinBoxs_jogAcc->value();
    axis->jogParam.dec = ui.doubleSpinBoxs_jogDec->value();
}

void CAxisWidget::onClearState()
{
	short axis = m_iAxisId;
	bool ok = m_pTotalMgr->axisMgr()->clearStatus(axis);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 状态已清除").arg(m_iAxisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 状态清除失败").arg(m_iAxisId), Qt::red);
	}
}

void CAxisWidget::onServoOn()
{
	short axis = m_iAxisId;
	bool ok = m_pTotalMgr->axisMgr()->enable(axis);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 使能成功").arg(m_iAxisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 使能失败").arg(m_iAxisId), Qt::red);
	}
}

void CAxisWidget::onServoOff()
{
	short axis = m_iAxisId;
	bool ok = m_pTotalMgr->axisMgr()->disable(axis);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 已禁止").arg(m_iAxisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 禁止失败").arg(m_iAxisId), Qt::red);
	}
}

void CAxisWidget::onClearPos()
{
	short axis = m_iAxisId;
	bool ok = m_pTotalMgr->axisMgr()->zeroPosition(axis);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 位置已清零").arg(m_iAxisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 位置清零失败").arg(m_iAxisId), Qt::red);
	}
}

void CAxisWidget::onSmoothStop()
{
	short axis = m_iAxisId;
	bool ok = m_pTotalMgr->axisMgr()->stop(axis, 1);  
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 减速停止").arg(m_iAxisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 减速停止失败").arg(m_iAxisId), Qt::red);
	}
}

void CAxisWidget::onEStop()
{
	short axis = m_iAxisId;
	bool ok = m_pTotalMgr->axisMgr()->stop(axis, 0);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 急停已触发").arg(m_iAxisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 急停失败").arg(m_iAxisId), Qt::red);
	}
}

void CAxisWidget::onTrapMotion()
{
	if (!m_pTotalMgr) return;
	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)m_pTotalMgr->axisCount()) return;
	const stuAxis* axis = m_pTotalMgr->getAxisRef(index);
	if (!axis) return;
	short axisId = m_iAxisId;
	bool ok = m_pTotalMgr->motionMgr()->startTrapMotion(axisId, axis->trapParam.stepSize);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 点位运动已启动").arg(axisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 运动启动失败，err=%1")
			.arg(m_pTotalMgr->motionMgr()->lastError()),
			Qt::red);
	}
}


void CAxisWidget::onJogPressed(int direction)
{
	if (!m_pTotalMgr) return;
	int index = m_iAxisId - 1;
	short axisId = m_iAxisId;
	stuAxis* axis = m_pTotalMgr->getAxisRef(index);
	if (!axis) return;
	bool ok = m_pTotalMgr->motionMgr()->setJogParam(axisId, axis->jogParam);
	if (!ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 写入Jog参数失败").arg(axisId), Qt::red);
		return;
	}
	ok = m_pTotalMgr->motionMgr()->startJogMotion(axisId, direction);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 %2Jog已启动")
			.arg(axisId)
			.arg(direction > 0 ? QStringLiteral("正向") : QStringLiteral("反向")),
			Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 Jog启动失败").arg(axisId), Qt::red);
	}
}

void CAxisWidget::onJogReleased()
{
	if (!m_pTotalMgr) return;
	short axisId = m_iAxisId;

	// 减速停止（option = 1）
	bool ok = m_pTotalMgr->axisMgr()->stop(axisId, 1);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 Jog停止").arg(axisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 Jog停止失败").arg(axisId), Qt::red);
	}
}


void CAxisWidget::onComboBoxCurrentIndexChanged(int index)
{
	m_iAxisId = index + 1;  

	if (m_pTotalMgr && m_pTotalMgr->boardMgr()->isOpen()) {
		// 切换到对应轴时，刷新点位运动参数显示
		stuAxis* axis = m_pTotalMgr->getAxisRef(index);
		if (axis) {
			ui.spinBox_trapMotionVel->setValue(axis->trapParam.dMotionVel);
			ui.doubleSpinBoxs_trapAcc->setValue(axis->trapParam.acc);
			ui.doubleSpinBoxs_trapDec->setValue(axis->trapParam.dec);
			ui.spinBox_trapStepSize->setValue(axis->trapParam.stepSize) ;
			ui.spinBox_trapSmoothTime->setValue(axis->trapParam.somoothTime);
			ui.spinBox_trapCycleTime->setValue(axis->trapParam.cycleTimes);
			ui.spinBox_TrapInPositionDelay->setValue(axis->trapParam.Delay);
		}
		// 刷新jog运动参数
		if (axis){
			ui.spinBox_jogMotionVel->setValue(axis->jogParam.dMotionVel);
            ui.doubleSpinBoxs_jogAcc->setValue(axis->jogParam.acc);
            ui.doubleSpinBoxs_jogDec->setValue(axis->jogParam.dec);
		}
		if (axis)
		{
			ui.comboBox_Mode->setCurrentIndex(axis->lPrfMode);
		}
	}
}

void CAxisWidget::onComboBoxModeCurrentIndexChanged(int index)
{
	if (m_pTotalMgr && m_pTotalMgr->boardMgr()->isOpen()) {

		int axisIdx = m_iAxisId - 1;
		stuAxis* axis = m_pTotalMgr->getAxisRef(axisIdx);
		if (axis) {
			bool ok = m_pTotalMgr->motionMgr()->setAxisMotionMode(axis->axisIndex, index);
			if (ok) {
				updateUIEnable(index);
				QString modeName = (index == 0) ? QStringLiteral("点位运动(trap)")
					: QStringLiteral("Jog运动");
				m_pGTSControllerWidget->showLog(
					QStringLiteral("轴%1 切换运动模式为 %2 成功")
					.arg(m_iAxisId).arg(modeName),
					Qt::darkGreen);
			}
			else {
				m_pGTSControllerWidget->showLog(
					QStringLiteral("轴%1 切换运动模式失败").arg(m_iAxisId),
					Qt::red);
			}
		}
	}
}


void CAxisWidget::onAxisUpdated(const std::vector<stuAxis>& axisInfo)
{
	m_bUpdatingFromBoard = true;
	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)axisInfo.size()) return;
	const stuAxis& axis = axisInfo[index];

	ui.radioButton_servoEnable->setChecked(axis.bServoOn);
	ui.radioButton_nLimit->setChecked(axis.bNegLimit);
	ui.radioButton_pLimit->setChecked(axis.bPosLimit);
	ui.radioButton_motionErr->setChecked(axis.bMError);
	ui.radioButton_sevorAlarm->setChecked(axis.bAlarm);
	ui.radioButton_eStop->setChecked(axis.bAbruptStop);
	ui.radioButton_smoothStop->setChecked(axis.bSmoothStop);
	ui.radioButton_motionSts->setChecked(axis.bMotion);
	ui.label_actPosData->setText(QString::number(axis.dCurPos, 'f', 3));
	ui.label_actVelData->setText(QString::number(axis.dCurVel, 'f', 3));
	ui.label_tgtAccData->setText(QString::number(axis.dPrfAcc, 'f', 3));
	ui.label_tgtPosData->setText(QString::number(axis.dPrfPos, 'f', 3));
	ui.label_tgtVelData->setText(QString::number(axis.dPrfVel, 'f', 3));
	if (axis.bServoOn)
	{
		ui.pushButton_sevorOn->setText(QStringLiteral("失能"));
	}
	else
	{
		ui.pushButton_sevorOn->setText(QStringLiteral("使能"));
	}
	m_bUpdatingFromBoard = false;
}
