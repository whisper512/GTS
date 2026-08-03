#include <QTimer>
#include <QPushButton>
#include <QFont>

#include "AxisWidget.h"
#include "../../GtsCore/GtsMgr.h"

CAxisWidget::CAxisWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initWidget();
	initConnections();
}

CAxisWidget::~CAxisWidget()
{
	m_gtsMgr = nullptr;
}


void CAxisWidget::setGtsTotalMgr(GtsMgr* mgr)
{
	if (m_gtsMgr)
	{
		disconnect(m_gtsMgr, &GtsMgr::axisUpdated, this, &CAxisWidget::onAxisUpdated);
		disconnect(m_gtsMgr, &GtsMgr::axisSettingUpdated, this, &CAxisWidget::onAxisSettingUpdated);
	}
	m_gtsMgr = mgr;
	if (m_gtsMgr)
	{
		connect(m_gtsMgr, &GtsMgr::axisUpdated, this, &CAxisWidget::onAxisUpdated);
		connect(m_gtsMgr, &GtsMgr::axisSettingUpdated, this, &CAxisWidget::onAxisSettingUpdated);
	}
}


void CAxisWidget::initWidget()
{
	ui.comboBox_axisID->addItem(QStringLiteral("轴 1"));
	ui.comboBox_axisID->addItem(QStringLiteral("轴 2"));
	ui.comboBox_axisID->addItem(QStringLiteral("轴 3"));
	ui.comboBox_axisID->addItem(QStringLiteral("轴 4"));

	ui.comboBox_Mode->addItem(QStringLiteral("点位运动(trap)"));
	ui.comboBox_Mode->addItem(QStringLiteral("Jog运动"));

	// RadioButton: disable auto-exclusive, block user clicks
	const QList<QRadioButton*> stateRadios = {
		ui.radioButton_servoEnable, ui.radioButton_sevorAlarm,
		ui.radioButton_nLimit,       ui.radioButton_pLimit,
		ui.radioButton_motionErr,    ui.radioButton_motionSts,
		ui.radioButton_eStop,        ui.radioButton_smoothStop,
	};
	for (QRadioButton* rb : stateRadios) {
		rb->setAutoExclusive(false);
		rb->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	}

	// Monospace font to prevent layout jitter on data refresh
	const QList<QLabel*> numLabels = {
		ui.label_actPosData,
		ui.label_actVelData,
		ui.label_tgtPosData,
		ui.label_tgtVelData,
		ui.label_tgtAccData,
		ui.label_tgtPosDataPluse,
		ui.label_tgtVelDataPluse,
		ui.label_tgtAccDataPluse,
	};
	QFont monoFont(QStringLiteral("Consolas"), 9);
	for (QLabel* lb : numLabels) {
		lb->setFont(monoFont);
		lb->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	}
}

void CAxisWidget::initConnections()
{
	QTimer::singleShot(0, this, [this]() {
		// Axis operation buttons
		connect(ui.pushButton_clearState, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
		connect(ui.pushButton_sevorOn, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
		connect(ui.pushButton_clearPos, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
		connect(ui.pushButton_smoothStop, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
		connect(ui.pushButton_eStop, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
		connect(ui.pushButton_TarpActMotion, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);

		// Jog press/release
		connect(ui.pushButton_jogPMotion, &QPushButton::pressed, this, [this]() { onJogPressed(1); });
		connect(ui.pushButton_jogPMotion, &QPushButton::released, this, [this]() { onJogReleased(); });
		connect(ui.pushButton_jogNMotion, &QPushButton::pressed, this, [this]() { onJogPressed(-1); });
		connect(ui.pushButton_jogNMotion, &QPushButton::released, this, [this]() { onJogReleased(); });

		// Combo boxes
		connect(ui.comboBox_axisID, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &CAxisWidget::onComboBoxCurrentIndexChanged);
		connect(ui.comboBox_Mode, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &CAxisWidget::onComboBoxModeCurrentIndexChanged);

		// Trap param changes
		connect(ui.spinBox_trapMotionVel, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
		connect(ui.doubleSpinBoxs_trapAcc, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
		connect(ui.doubleSpinBoxs_trapDec, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
		connect(ui.doubleSpinBox_trapLengthMm, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
		connect(ui.spinBox_trapSmoothTime, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
		connect(ui.spinBox_trapCycleTime, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);
		connect(ui.spinBox_TrapInPositionDelay, &QSpinBox::editingFinished, this, &CAxisWidget::onTrapParamChanged);

		// Jog param changes
		connect(ui.doubleSpinBoxs_jogAcc, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onJogParamChanged);
		connect(ui.doubleSpinBoxs_jogDec, &QDoubleSpinBox::editingFinished, this, &CAxisWidget::onJogParamChanged);
	});
}

void CAxisWidget::connectAxisSignals()
{
}


void CAxisWidget::updateUIEnable(int index)
{
	if (index == 0) {
		// Trap mode
		ui.spinBox_jogMotionVel->setEnabled(false);
		ui.doubleSpinBoxs_jogAcc->setEnabled(false);
		ui.doubleSpinBoxs_jogDec->setEnabled(false);
		ui.pushButton_jogPMotion->setEnabled(false);
		ui.pushButton_jogNMotion->setEnabled(false);

		ui.spinBox_trapMotionVel->setEnabled(true);
		ui.doubleSpinBoxs_trapAcc->setEnabled(true);
		ui.doubleSpinBoxs_trapDec->setEnabled(true);
		ui.doubleSpinBox_trapLengthMm->setEnabled(true);
		ui.spinBox_trapSmoothTime->setEnabled(true);
		ui.spinBox_trapCycleTime->setEnabled(true);
		ui.spinBox_TrapInPositionDelay->setEnabled(true);
		ui.pushButton_TarpActMotion->setEnabled(true);
	}
	else {
		// Jog mode
		ui.spinBox_jogMotionVel->setEnabled(true);
		ui.doubleSpinBoxs_jogAcc->setEnabled(true);
		ui.doubleSpinBoxs_jogDec->setEnabled(true);
		ui.pushButton_jogPMotion->setEnabled(true);
		ui.pushButton_jogNMotion->setEnabled(true);

		ui.spinBox_trapMotionVel->setEnabled(false);
		ui.doubleSpinBoxs_trapAcc->setEnabled(false);
		ui.doubleSpinBoxs_trapDec->setEnabled(false);
		ui.doubleSpinBox_trapLengthMm->setEnabled(false);
		ui.spinBox_trapSmoothTime->setEnabled(false);
		ui.spinBox_trapCycleTime->setEnabled(false);
		ui.spinBox_TrapInPositionDelay->setEnabled(false);
		ui.pushButton_TarpActMotion->setEnabled(false);
	}
}


// ==================== Axis Operations ====================

void CAxisWidget::onClearState()
{
	if (!m_gtsMgr) return;
	m_gtsMgr->axisMgr()->clearStatus(m_axisId);
}

void CAxisWidget::onServoOn()
{
	if (!m_gtsMgr) return;
	m_gtsMgr->axisMgr()->enable(m_axisId);
}

void CAxisWidget::onServoOff()
{
	if (!m_gtsMgr) return;
	m_gtsMgr->axisMgr()->disable(m_axisId);
}

void CAxisWidget::onClearPos()
{
	if (!m_gtsMgr) return;
	m_gtsMgr->axisMgr()->zeroPosition(m_axisId);
}

void CAxisWidget::onSmoothStop()
{
	if (!m_gtsMgr) return;
	m_gtsMgr->axisMgr()->stop(m_axisId, 1);
}

void CAxisWidget::onEStop()
{
	if (!m_gtsMgr) return;
	m_gtsMgr->axisMgr()->stop(m_axisId, 0);
}

void CAxisWidget::onTrapMotion()
{
	if (!m_gtsMgr) return;
	int index = m_axisId - 1;
	if (index < 0 || index >= (int)m_gtsMgr->axisCount()) return;
	m_gtsMgr->motionMgr()->trapMotion(m_axisId,
		m_gtsMgr->axisCfg()->axes[index].trapParam.lengthMm);
}

void CAxisWidget::onJogPressed(int direction)
{
	if (!m_gtsMgr) return;
	int index = m_axisId - 1;
	if (index < 0 || index >= (int)m_gtsMgr->axisCount()) return;
	m_gtsMgr->motionMgr()->setJogParam(m_axisId,
		m_gtsMgr->axisCfg()->axes[index].jogParam);
	m_gtsMgr->motionMgr()->startJogMotion(m_axisId, direction);
}

void CAxisWidget::onJogReleased()
{
	if (!m_gtsMgr) return;
	// Deceleration stop (option = 1)
	m_gtsMgr->axisMgr()->stop(m_axisId, 1);
}


void CAxisWidget::onTrapParamChanged()
{
	if (m_updatingFromBoard) return;
	if (!m_gtsMgr) return;
	int index = m_axisId - 1;
	if (index < 0 || index >= (int)m_gtsMgr->axisCount()) return;

	auto& tp = m_gtsMgr->axisCfg()->axes[index].trapParam;
	tp.motionVel = ui.spinBox_trapMotionVel->value();
	tp.acc = ui.doubleSpinBoxs_trapAcc->value();
	tp.dec = ui.doubleSpinBoxs_trapDec->value();
	tp.lengthMm = ui.doubleSpinBox_trapLengthMm->value();
	tp.somoothTime = ui.spinBox_trapSmoothTime->value();
	tp.cycleTimes = ui.spinBox_trapCycleTime->value();
	tp.delay = ui.spinBox_TrapInPositionDelay->value();
}

void CAxisWidget::onJogParamChanged()
{
	if (m_updatingFromBoard) return;
	if (!m_gtsMgr) return;
	int index = m_axisId - 1;
	if (index < 0 || index >= (int)m_gtsMgr->axisCount()) return;

	auto& jp = m_gtsMgr->axisCfg()->axes[index].jogParam;
	jp.motionVel = ui.spinBox_jogMotionVel->value();
	jp.acc = ui.doubleSpinBoxs_jogAcc->value();
	jp.dec = ui.doubleSpinBoxs_jogDec->value();
}


void CAxisWidget::onComboBoxCurrentIndexChanged(int index)
{
	m_axisId = index + 1;
	if (!m_gtsMgr || !m_gtsMgr->boardMgr()->isOpen()) return;

	const auto& tp = m_gtsMgr->axisCfg()->axes[index].trapParam;
	ui.spinBox_trapMotionVel->setValue(tp.motionVel);
	ui.doubleSpinBoxs_trapAcc->setValue(tp.acc);
	ui.doubleSpinBoxs_trapDec->setValue(tp.dec);
	ui.doubleSpinBox_trapLengthMm->setValue(tp.lengthMm);
	ui.spinBox_trapSmoothTime->setValue(tp.somoothTime);
	ui.spinBox_trapCycleTime->setValue(tp.cycleTimes);
	ui.spinBox_TrapInPositionDelay->setValue(tp.delay);

	const auto& jp = m_gtsMgr->axisCfg()->axes[index].jogParam;
	ui.spinBox_jogMotionVel->setValue(jp.motionVel);
	ui.doubleSpinBoxs_jogAcc->setValue(jp.acc);
	ui.doubleSpinBoxs_jogDec->setValue(jp.dec);

	SingleAxisInfo* axis = m_gtsMgr->getAxisRef(index);
	if (axis)
		ui.comboBox_Mode->setCurrentIndex(axis->prfMode);
}

void CAxisWidget::onComboBoxModeCurrentIndexChanged(int index)
{
	if (!m_gtsMgr || !m_gtsMgr->boardMgr()->isOpen()) return;

	int axisIdx = m_axisId - 1;
	SingleAxisInfo* axis = m_gtsMgr->getAxisRef(axisIdx);
	if (!axis) return;

	bool ok = m_gtsMgr->motionMgr()->setAxisMotionMode(axis->axisIndex, index);
	if (ok)
		updateUIEnable(index);
}


void CAxisWidget::onAxisUpdated(const std::vector<SingleAxisInfo>& axisInfo)
{
	m_updatingFromBoard = true;
	int index = m_axisId - 1;
	if (index < 0 || index >= (int)axisInfo.size()) return;
	const SingleAxisInfo& axis = axisInfo[index];

	// Status indicators
	ui.radioButton_servoEnable->setChecked(axis.isServoOn);
	ui.radioButton_nLimit->setChecked(axis.isNegLimit);
	ui.radioButton_pLimit->setChecked(axis.isPosLimit);
	ui.radioButton_motionErr->setChecked(axis.isMError);
	ui.radioButton_sevorAlarm->setChecked(axis.isAlarm);
	ui.radioButton_eStop->setChecked(axis.isAbruptStop);
	ui.radioButton_smoothStop->setChecked(axis.isSmoothStop);
	ui.radioButton_motionSts->setChecked(axis.isMotion);

	// Encoder values
	ui.label_actPosData->setText(QString::number(axis.encPosMm, 'f', 3));
	ui.label_actVelData->setText(QString::number(axis.encVelMm, 'f', 3));

	// Planner values (mm)
	ui.label_tgtPosData->setText(QString::number(axis.prfPosMm, 'f', 3));
	ui.label_tgtVelData->setText(QString::number(axis.prfVelMm, 'f', 3));
	ui.label_tgtAccData->setText(QString::number(axis.prfAccMm, 'f', 3));

	// Planner values (pulse)
	ui.label_tgtPosDataPluse->setText(QString::number(axis.prfPosOriginal, 'f', 3));
	ui.label_tgtVelDataPluse->setText(QString::number(axis.prfVelOriginal, 'f', 3));
	ui.label_tgtAccDataPluse->setText(QString::number(axis.prfAccOriginal, 'f', 3));

	// Servo on/off button text
	if (axis.isServoOn)
		ui.pushButton_sevorOn->setText(QStringLiteral("失能"));
	else
		ui.pushButton_sevorOn->setText(QStringLiteral("使能"));

	m_updatingFromBoard = false;
}

void CAxisWidget::onAxisSettingUpdated(const std::vector<SingleAxisInfo>& axisInfo)
{
	m_updatingFromBoard = true;
	int index = m_axisId - 1;
	if (index < 0 || index >= (int)axisInfo.size()) return;
	const SingleAxisInfo& axis = axisInfo[index];

	ui.comboBox_Mode->setCurrentIndex(axis.prfMode);

	const auto& tp = m_gtsMgr->axisCfg()->axes[index].trapParam;
	ui.spinBox_trapMotionVel->setValue((int)tp.motionVel);
	ui.doubleSpinBox_trapLengthMm->setValue(tp.lengthMm);
	ui.doubleSpinBoxs_trapAcc->setValue(tp.acc);
	ui.doubleSpinBoxs_trapDec->setValue(tp.dec);
	ui.spinBox_trapSmoothTime->setValue(tp.somoothTime);
	ui.spinBox_trapCycleTime->setValue(tp.cycleTimes);
	ui.spinBox_TrapInPositionDelay->setValue(tp.delay);

	const auto& jp = m_gtsMgr->axisCfg()->axes[index].jogParam;
	ui.spinBox_jogMotionVel->setValue(jp.motionVel);
	ui.doubleSpinBoxs_jogAcc->setValue(jp.acc);
	ui.doubleSpinBoxs_jogDec->setValue(jp.dec);

	updateUIEnable(ui.comboBox_Mode->currentIndex());
	m_updatingFromBoard = false;
}


void CAxisWidget::onBtnClick()
{
	if (!m_gtsMgr) return;
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;

	QString objName = btn->objectName();
	if (objName == "pushButton_clearState") {
		onClearState();
	}
	else if (objName == "pushButton_sevorOn") {
		if (ui.pushButton_sevorOn->text() == QStringLiteral("使能"))
			onServoOn();
		else
			onServoOff();
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
