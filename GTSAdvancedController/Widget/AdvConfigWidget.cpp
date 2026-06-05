#include <QTimer>
#include <QFileDialog>
#include "AdvConfigWidget.h"
#include "AdvGTSControllerWidget.h"
#include "../Mgr/AdvTotalMgr.h"

CConfigWidget::CConfigWidget(QWidget *parent, CTotalMgr* mgr)
	: QMainWindow(parent)
	, m_pTotalMgr(mgr)
{
	ui.setupUi(this);
	m_pGTSControllerWidget = qobject_cast<GTSControllerWidget*>(parent);
	InitConfigWidget();
}

CConfigWidget::~CConfigWidget()
{}

void CConfigWidget::InitConfigWidget()
{
	QTimer::singleShot(100, this, [this]() {
		InitUI();

		});
	connectSignalsAndSlots();

}

void CConfigWidget::InitUI()
{
	ComboAddNumbers(ui.comboBox_axisId, 4);
	ComboAddNumbers(ui.comboBox_stepIndex, 4);
	ComboAddNumbers(ui.comboBox_dacId, 4);
	ComboAddNumbers(ui.comboBox_encoderId, 4);
	ComboAddNumbers(ui.comboBox_controlId, 4);
	ComboAddNumbers(ui.comboBox_profileId, 4);
	ComboAddNumbers(ui.comboBox_inputID, 16);
	ComboAddNumbers(ui.comboBox_inputID, 16);
	ComboAddNumbers(ui.comboBox_smoothStopinputID, 16);
	ComboAddNumbers(ui.comboBox_eStopinputID, 16);

	ui.groupBox_encoderEquivalent->setVisible(false);
	ComboAddItems(ui.comboBox_pulseOutputMode,{ QStringLiteral("脉冲+方向") , QStringLiteral("CCW/CW")});
	ComboAddItems(ui.comboBox_inputPulseInvert, { QStringLiteral("正常"), QStringLiteral("取反") });
	ComboAddItems(ui.comboBox_pulseCountSource, { QStringLiteral("外部编码器"), QStringLiteral("脉冲计数器") });
	ComboAddItems(ui.comboBox_limitSwitchLevel, {QStringLiteral("高电平触发"),QStringLiteral("低电平触发")});
	ComboAddItems(ui.comboBox_axsiOutputMode, { QStringLiteral("闭环控制(模拟量)"),QStringLiteral("开环控制(脉冲)") });
	ComboAddItems(ui.comboBox_smoothStopInputType, { QStringLiteral("正限位"), QStringLiteral("负限位"),QStringLiteral("驱动报警"), QStringLiteral("原点"), QStringLiteral("通用输入") });
	ComboAddItems(ui.comboBox_eStopInputType, { QStringLiteral("正限位"), QStringLiteral("负限位"),QStringLiteral("驱动报警"), QStringLiteral("原点"), QStringLiteral("通用输入") });
	ComboAddItems(ui.comboBox_activeLevel, {QStringLiteral("正常"),QStringLiteral("取反")});
}

void CConfigWidget::connectSignalsAndSlots()
{
	connect(ui.pushButton_servoAlarmEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.pushButton_limitEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.pushButton_loadToBoard, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.spinBox_profileEquivalentAlpha, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onProfileScaleChanged);
	connect(ui.spinBox_profileEquivalentBeta, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onProfileScaleChanged);
	connect(ui.comboBox_pulseOutputMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CConfigWidget::onPulseOutputModeChanged);
	connect(ui.spinBox_zeroOffsetCompensation, &QAbstractSpinBox::editingFinished,	this, &CConfigWidget::onDacBiasChanged);
	connect(ui.spinBox_outputVoltageSaturationLimit, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onDacLimitChanged);
	connect(ui.comboBox_dacId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshDacValues(); });
	connect(ui.comboBox_inputPulseInvert, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onInputPulseInvertChanged);
	connect(ui.comboBox_pulseCountSource, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onPulseCountSourceChanged);
	connect(ui.spinBox_followingErrorLimit, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onFollowErrorLimitChanged);
	connect(ui.comboBox_controlId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshFollowErrorLimit(); });
	connect(ui.doubleSpinBox_smoothStopDec, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onStopDecelChanged);
	connect(ui.doubleSpinBox_smoothStopDec_2, &QAbstractSpinBox::editingFinished,	this, &CConfigWidget::onStopDecelChanged);
	connect(ui.comboBox_profileId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshStopDecel(); });
	connect(ui.comboBox_limitSwitchLevel, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onLimitSwitchLevelChanged);
	connect(ui.comboBox_axsiOutputMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CConfigWidget::onAxisCtrlModeChanged);
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshAxisCtrlMode(); });
	connect(ui.comboBox_smoothStopInputType, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onSmoothStopIOChanged);
	connect(ui.comboBox_smoothStopinputID, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onSmoothStopIOChanged);
	// 急停 IO
	connect(ui.comboBox_eStopInputType, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onEStopIOChanged);
	connect(ui.comboBox_eStopinputID, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onEStopIOChanged);
	// 切轴刷新
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshStopIO(); });
	// GPI 电平极性
	connect(ui.comboBox_inputID, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshGpiSense(); });
	connect(ui.comboBox_activeLevel, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &CConfigWidget::onGpiSenseChanged);
	// 轴号变化
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() {refreshAlarmButton(); refreshLimitButton(); refreshScaleEquivalents();
	refreshAxisCtrlMode(); });
	// stepID变化
	connect(ui.comboBox_stepIndex, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshStepPulseMode(); });
	// encoderID变化
	connect(ui.comboBox_encoderId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshEncoderConfig(); });
	//connect(ui.spinBox_encoderEquivalentAlpha, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onEncoderScaleChanged);
    //connect(ui.spinBox_encoderEquivalentBeta, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onEncoderScaleChanged);
}

void CConfigWidget::onBtnClicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;

	QString objName = btn->objectName();

	if (objName == "pushButton_servoAlarmEnable") {
		onservoAlarmEnable();
	}
	else if (objName == "pushButton_limitEnable") {
		onLimitEnable();
	}
	else if (objName == "pushButton_loadToBoard") {
		onLoadToBoard();
	}
}

void CConfigWidget::onLoadToBoard()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("选择配置文件"),
		QString(),
		QStringLiteral("配置文件 (*.cfg *.CFG);;所有文件 (*.*)")
	);
	if (filePath.isEmpty()) return;
	short ret = GtsHal::loadConfig(filePath.toLocal8Bit().constData());
	if (ret == 0) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("配置文件加载成功: %1").arg(filePath),
			Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("配置文件加载失败 (err=%1): %2")
			.arg(ret)
			.arg(filePath),
			Qt::red);
	}
}

void CConfigWidget::onservoAlarmEnable()
{
	if (!m_pTotalMgr) return;
	short axis = ui.comboBox_axisId->currentText().toShort();
	if (!m_pTotalMgr->isAlarmAvailable(axis)) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 报警信号不可用(配置文件未启用)").arg(axis),
			Qt::yellow);
		return;
	}
	bool now = m_pTotalMgr->toggleAlarm(axis);
	ui.pushButton_servoAlarmEnable->setText(
		now ? QStringLiteral("报警:有效") : QStringLiteral("报警:无效"));
	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 报警信号 → %2")
		.arg(axis)
		.arg(now ? QStringLiteral("有效") : QStringLiteral("无效")),
		now ? Qt::darkGreen : Qt::gray);
}


void CConfigWidget::onAlarmStateChanged()
{
	refreshAlarmButton();
	refreshLimitButton();
	//refreshScaleEquivalents();
	//refreshDacValues();
	//refreshFollowErrorLimit();
	//refreshStopDecel();
	//refreshAxisCtrlMode();
	//refreshStopIO();
	//refreshGpiSense();
}

void CConfigWidget::refreshAlarmButton()
{
	if (!m_pTotalMgr) {
		return;
	}
	m_bRefreshing = true;
	short axis = ui.comboBox_axisId->currentText().toShort();
	bool avail = m_pTotalMgr->isAlarmAvailable(axis);
	bool active = m_pTotalMgr->isAlarmActive(axis);
	if (avail) {
		ui.pushButton_servoAlarmEnable->setEnabled(true);
		ui.pushButton_servoAlarmEnable->setText(
			active ? QStringLiteral("报警:有效") : QStringLiteral("报警:无效"));
	}
	else {
		ui.pushButton_servoAlarmEnable->setEnabled(false);
		ui.pushButton_servoAlarmEnable->setText(QStringLiteral("报警:不支持"));
	}
	m_bRefreshing = false;
}

void CConfigWidget::onLimitEnable()
{
	if (!m_pTotalMgr) return;
	short axis = ui.comboBox_axisId->currentText().toShort();

	if (!m_pTotalMgr->isLimitAvailable(axis)) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("轴%1 限位不可用（配置文件未启用）").arg(axis),
			Qt::yellow);
		return;
	}

	bool now = m_pTotalMgr->toggleLimit(axis);

	ui.pushButton_limitEnable->setText(
		now ? QStringLiteral("限位:有效") : QStringLiteral("限位:无效"));

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 限位 → %2")
		.arg(axis)
		.arg(now ? QStringLiteral("有效") : QStringLiteral("无效")),
		now ? Qt::darkGreen : Qt::gray);
}

void CConfigWidget::refreshLimitButton()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short axis = ui.comboBox_axisId->currentText().toShort();

	if (m_pTotalMgr->isLimitAvailable(axis)) {
		ui.pushButton_limitEnable->setEnabled(true);
		ui.pushButton_limitEnable->setText(
			m_pTotalMgr->isLimitActive(axis)
			? QStringLiteral("限位:有效")
			: QStringLiteral("限位:无效"));
	}
	else {
		ui.pushButton_limitEnable->setEnabled(false);
		ui.pushButton_limitEnable->setText(QStringLiteral("限位:不支持"));
	}
	m_bRefreshing = false;
}

void CConfigWidget::refreshScaleEquivalents()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short axis = ui.comboBox_axisId->currentText().toShort();
	short encoder = ui.comboBox_encoderId->currentText().toShort();

	ui.spinBox_profileEquivalentAlpha->setValue(
		(int)m_pTotalMgr->profileScaleAlpha(axis));
	ui.spinBox_profileEquivalentBeta->setValue(
		(int)m_pTotalMgr->profileScaleBeta(axis));
	ui.spinBox_encoderEquivalentAlpha->setValue(
		(int)m_pTotalMgr->encScaleAlpha(encoder));
	ui.spinBox_encoderEquivalentBeta->setValue(
		(int)m_pTotalMgr->encScaleBeta(encoder));
	m_bRefreshing = false;
}

void CConfigWidget::refreshStepPulseMode()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short step = ui.comboBox_stepIndex->currentText().toShort();
	ui.comboBox_pulseOutputMode->setCurrentIndex(
		(int)m_pTotalMgr->stepPulseMode(step));
	m_bRefreshing = false;
}

void CConfigWidget::refreshEncoderConfig()
{
	if (!m_pTotalMgr) return;
	short encoder = ui.comboBox_encoderId->currentText().toShort();

	m_bRefreshing = true;
	ui.comboBox_inputPulseInvert->setCurrentIndex(
		m_pTotalMgr->encoderInvert(encoder) ? 1 : 0);
	ui.comboBox_pulseCountSource->setCurrentIndex(
		m_pTotalMgr->encoderPulseCount(encoder) ? 1 : 0);
	m_bRefreshing = false;
}


void CConfigWidget::onProfileScaleChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	short axis = ui.comboBox_axisId->currentText().toShort();
	long alpha = ui.spinBox_profileEquivalentAlpha->value();
	long beta = ui.spinBox_profileEquivalentBeta->value();
	m_pTotalMgr->setProfileScale(axis, alpha, beta);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 规划器当量 → α=%2 β=%3").arg(axis).arg(alpha).arg(beta),
		Qt::darkGreen);
}

void CConfigWidget::onEncoderScaleChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	short encoder = ui.comboBox_encoderId->currentText().toShort();
	long alpha = ui.spinBox_encoderEquivalentAlpha->value();
	long beta = ui.spinBox_encoderEquivalentBeta->value();
	m_pTotalMgr->setEncoderScale(encoder, alpha, beta);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("编码器%1 当量 → α=%2 β=%3").arg(encoder).arg(alpha).arg(beta),
		Qt::darkGreen);
}

void CConfigWidget::onPulseOutputModeChanged(int index)
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;
	short step = ui.comboBox_stepIndex->currentText().toShort();
	m_pTotalMgr->setStepPulseMode(step, (short)index);
	const char* names[] = { "脉冲+方向", "CCW/CW" };
	m_pGTSControllerWidget->showLog(
		QStringLiteral("Step%1 脉冲输出模式 → %2").arg(step).arg(names[index]),
		Qt::darkGreen);
}

void CConfigWidget::refreshDacValues()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short dac = ui.comboBox_dacId->currentText().toShort();

	ui.spinBox_zeroOffsetCompensation->setValue(
		(int)m_pTotalMgr->dacBias(dac));
	ui.spinBox_outputVoltageSaturationLimit->setValue(
		(int)m_pTotalMgr->dacLimit(dac));
	m_bRefreshing = false;
}

void CConfigWidget::onDacBiasChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short dac = ui.comboBox_dacId->currentText().toShort();
	short bias = (short)ui.spinBox_zeroOffsetCompensation->value();
	m_pTotalMgr->setDacBias(dac, bias);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("DAC%1 零漂补偿 → %2").arg(dac).arg(bias),
		Qt::darkGreen);
}

void CConfigWidget::onDacLimitChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short dac = ui.comboBox_dacId->currentText().toShort();
	short limit = (short)ui.spinBox_outputVoltageSaturationLimit->value();
	m_pTotalMgr->setDacLimit(dac, limit);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("DAC%1 饱和极限 → %2").arg(dac).arg(limit),
		Qt::darkGreen);
}

void CConfigWidget::onInputPulseInvertChanged(int index)
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;
	short encoder = ui.comboBox_encoderId->currentText().toShort();
	bool invert = (index == 1);
	m_pTotalMgr->setEncoderInvert(encoder, invert);
	m_pGTSControllerWidget->showLog(
		QStringLiteral("编码器%1 极性 → %2")
		.arg(encoder)
		.arg(invert ? QStringLiteral("取反") : QStringLiteral("正常")),
		Qt::darkGreen);
}

void CConfigWidget::onPulseCountSourceChanged(int index)
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;
	short encoder = ui.comboBox_encoderId->currentText().toShort();
	bool isPulse = (index == 1);
	m_pTotalMgr->setEncoderPulseCount(encoder, isPulse);
	// 注意：index=0 是外部编码器，index=1 是脉冲计数器
	QString strLogCounter = index == 1 ? QStringLiteral("脉冲计数器") : QStringLiteral("外部编码器");
	m_pGTSControllerWidget->showLog(
		QStringLiteral("编码器%1 计数源 → %2").arg(encoder).arg(strLogCounter),
		Qt::darkGreen);
}

void CConfigWidget::refreshFollowErrorLimit()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short ctrl = ui.comboBox_controlId->currentText().toShort();
	ui.spinBox_followingErrorLimit->setValue(
		(int)m_pTotalMgr->followErrorLimit(ctrl));
	m_bRefreshing = false;
}

void CConfigWidget::onFollowErrorLimitChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short ctrl = ui.comboBox_controlId->currentText().toShort();
	long error = ui.spinBox_followingErrorLimit->value();
	m_pTotalMgr->setFollowErrorLimit(ctrl, error);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("Control%1 跟随误差极限 → %2").arg(ctrl).arg(error),
		Qt::darkGreen);
}

void CConfigWidget::refreshStopDecel()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short profile = ui.comboBox_profileId->currentText().toShort();

	ui.doubleSpinBox_smoothStopDec->setValue(
		m_pTotalMgr->smoothStopDec(profile));
	ui.doubleSpinBox_smoothStopDec_2->setValue(
		m_pTotalMgr->estopDec(profile));
	m_bRefreshing = false;
}

void CConfigWidget::onStopDecelChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short profile = ui.comboBox_profileId->currentText().toShort();
	double smooth = ui.doubleSpinBox_smoothStopDec->value();
	double abrupt = ui.doubleSpinBox_smoothStopDec_2->value();

	m_pTotalMgr->setStopDecel(profile, smooth, abrupt);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("Profile%1 停止减速度 → 平滑=%2 急停=%3")
		.arg(profile).arg(smooth, 0, 'f', 3).arg(abrupt, 0, 'f', 3),
		Qt::darkGreen);
}

void CConfigWidget::onLimitSwitchLevelChanged(int index)
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	// 0=高电平触发(所有位=0)，1=低电平触发(轴1~4位全置1)
	unsigned short sense = (index == 0) ? 0 : 0x000F;

	bool ok = m_pTotalMgr->axisMgr()->setLimitSense(sense);

	QString level = (index == 0) ? QStringLiteral("高电平触发") : QStringLiteral("低电平触发");
	if (ok) {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("限位触发电平 → %1").arg(level),
			Qt::darkGreen);
	}
	else {
		m_pGTSControllerWidget->showLog(
			QStringLiteral("设置限位触发电平失败 (err=%1)")
			.arg(m_pTotalMgr->axisMgr()->lastError()),
			Qt::red);
	}
}

void CConfigWidget::refreshAxisCtrlMode()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short axis = ui.comboBox_axisId->currentText().toShort();
	ui.comboBox_axsiOutputMode->setCurrentIndex(
		(int)m_pTotalMgr->axisCtrlMode(axis));
	m_bRefreshing = false;
}

void CConfigWidget::onAxisCtrlModeChanged(int index)
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	m_pTotalMgr->setAxisCtrlMode(axis, (short)index);

	QString strMode;
	index == 0 ? strMode = QStringLiteral("闭环模式(模拟)") : strMode = QStringLiteral("开环模式(脉冲)");
	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 控制模式 → %2").arg(axis).arg(strMode),
		Qt::darkGreen);
}

void CConfigWidget::refreshStopIO()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short axis = ui.comboBox_axisId->currentText().toShort();

	ui.comboBox_smoothStopInputType->setCurrentIndex(
		(int)m_pTotalMgr->stopInputType(axis, 1));
	ui.comboBox_smoothStopinputID->setCurrentIndex(
		(int)m_pTotalMgr->stopInputIndex(axis, 1) - 1);
	ui.comboBox_eStopInputType->setCurrentIndex(
		(int)m_pTotalMgr->stopInputType(axis, 0));
	ui.comboBox_eStopinputID->setCurrentIndex(
		(int)m_pTotalMgr->stopInputIndex(axis, 0) - 1);
	m_bRefreshing = false;
}

void CConfigWidget::onSmoothStopIOChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	short inputType = (short)ui.comboBox_smoothStopInputType->currentIndex();
	short inputIdx = (short)(ui.comboBox_smoothStopinputID->currentIndex() + 1);

	m_pTotalMgr->setStopIO(axis, 1, inputType, inputIdx);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 平滑停止IO → %2[%3]")
		.arg(axis)
		.arg(DITypeToString(static_cast<DIType>(inputType)))
		.arg(inputIdx),
		Qt::darkGreen);
}

void CConfigWidget::onEStopIOChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	short inputType = (short)ui.comboBox_eStopInputType->currentIndex();
	short inputIdx = (short)(ui.comboBox_eStopinputID->currentIndex() + 1);

	m_pTotalMgr->setStopIO(axis, 0, inputType, inputIdx);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 急停IO → %2[%3]")
		.arg(axis)
		.arg(DITypeToString(static_cast<DIType>(inputType)))
		.arg(inputIdx),
		Qt::darkGreen);
}

void CConfigWidget::refreshGpiSense()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short diIndex = (short)(ui.comboBox_inputID->currentIndex() + 1);

	ui.comboBox_activeLevel->setCurrentIndex(
		m_pTotalMgr->isGpiSenseInvert(diIndex) ? 1 : 0);
	m_bRefreshing = false;
}

void CConfigWidget::onGpiSenseChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short diIndex = (short)(ui.comboBox_inputID->currentIndex() + 1);
	bool invert = (ui.comboBox_activeLevel->currentIndex() == 1);

	m_pTotalMgr->setGpiSenseBit(diIndex, invert);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("DI%1 电平逻辑 → %2")
		.arg(diIndex)
		.arg(invert ? QStringLiteral("取反") : QStringLiteral("正常")),
		Qt::darkGreen);
}
