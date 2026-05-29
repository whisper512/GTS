#include "AxisWidget.h"
#include "GTSControllerWidget.h"
#include "TotalMgr.h"
#include "BoardMgr.h"
#include "AxisMgr.h"

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
	connect(ui.pushButton_clearState, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_sevorOn, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_clearPos, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_smoothStop, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_eStop, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
	connect(ui.pushButton_TarpActMotion, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);

	connect(ui.spinBox_trapVel, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &CAxisWidget::onTrapParamChanged);
	connect(ui.doubleSpinBoxs_trapAcc, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, &CAxisWidget::onTrapParamChanged);
	connect(ui.doubleSpinBoxs_trapDec, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_trapStepSize, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_trapSmoothTime, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_trapCycleTime, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &CAxisWidget::onTrapParamChanged);
	connect(ui.spinBox_TrapInPositionDelay, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &CAxisWidget::onTrapParamChanged);
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
	else if (objName == "pushButton_ActMotion") {
		onActMotion();
	}
}

void CAxisWidget::onTrapParamChanged()
{
	if (m_bUpdatingFromBoard) return;
	if (!m_pTotalMgr) return;
	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)m_pTotalMgr->axisCount()) return;
	// 只更新内存，不写板卡
	stuAxis& axis = m_pTotalMgr->getAxisRef(index);
	axis.trapParam.vel = ui.spinBox_trapVel->value();
	axis.trapParam.acc = ui.doubleSpinBoxs_trapAcc->value();
	axis.trapParam.dec = ui.doubleSpinBoxs_trapDec->value();
	axis.trapParam.stepSize = ui.spinBox_trapStepSize->value();
	axis.trapParam.somoothTime = ui.spinBox_trapSmoothTime->value();
	axis.trapParam.cycleTimes = ui.spinBox_trapCycleTime->value();
	axis.trapParam.Delay = ui.spinBox_TrapInPositionDelay->value();
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

void CAxisWidget::onActMotion()
{
	if (!m_pTotalMgr) return;
	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)m_pTotalMgr->axisCount()) return;
	
	const stuAxis& axis = m_pTotalMgr->getAxisRef(index);
	short axisId = m_iAxisId;
	
	bool ok = m_pTotalMgr->motionMgr()->setTrapParam(axisId, axis.trapParam);
	if (!ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 写入点位参数失败").arg(axisId), Qt::red);
		return;
	}
	
	ok = m_pTotalMgr->motionMgr()->startTrapMotion(axisId, axis.trapParam.stepSize);
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 点位运动已启动").arg(axisId), Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 运动启动失败").arg(axisId), Qt::red);
	}
}




void CAxisWidget::onComboBoxCurrentIndexChanged(int index)
{
	m_iAxisId = index + 1;  

	if (m_pTotalMgr && m_pTotalMgr->boardMgr()->isOpen()) {
	}
}

void CAxisWidget::onAxisUpdated(const std::vector<stuAxis>& axisInfo)
{
	m_bUpdatingFromBoard = true;

	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)axisInfo.size()) return;
	stuAxis axis = axisInfo[index];

	// 轴状态
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
	ui.label_motionModeData->setText(motionModeToString(axis.lPrfMode));

	// 点位运动
	ui.spinBox_trapVel->setValue(axis.trapParam.vel);
	ui.doubleSpinBoxs_trapAcc->setValue(axis.trapParam.acc);
    ui.doubleSpinBoxs_trapDec->setValue(axis.trapParam.dec);
	ui.spinBox_trapStepSize->setValue(axis.trapParam.stepSize);
	ui.spinBox_trapSmoothTime->setValue(axis.trapParam.somoothTime);
	ui.spinBox_trapCycleTime->setValue(axis.trapParam.cycleTimes);
	ui.spinBox_TrapInPositionDelay->setValue(axis.trapParam.Delay);

	 
	if (axis.bServoOn)
	{
        ui.pushButton_sevorOn->setText(QStringLiteral("失能"));
	}
	else 
	{
		ui.pushButton_sevorOn->setText(QStringLiteral("使能"));
	}

	m_bUpdatingFromBoard = false;  // 恢复标志

	//QString statusStr = QStringLiteral(
	//	"轴%1 | 位置:%2 | 速度:%3 | 加速度:%4 | "
	//	"使能:%5 | 报警:%6 | 运动:%7 | 正限位:%8 | 负限位:%9 | "
	//	"误差:%10 | 急停:%11 | 平滑停止:%12"
	//    "运动模式:%13" )
	//	
	//	.arg(axis.axisIndex)
	//	.arg(axis.dCurPos, 0, 'f', 3)
	//	.arg(axis.dCurVel, 0, 'f', 3)
	//	.arg(axis.dCurAcc, 0, 'f', 3)
	//	.arg(axis.bServoOn ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.bAlarm ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.bMotion ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.bPosLimit ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.bNegLimit ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.bMError ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.bAbruptStop ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.bSmoothStop ? QStringLiteral("是") : QStringLiteral("否"))
	//	.arg(axis.lPrfMode);
	//m_pGTSControllerWidget->showLog(statusStr, Qt::darkCyan);
}
