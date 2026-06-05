#include <QTimer>
#include <QFileDialog>
#include "ConfigWidget.h"
#include "GTSControllerWidget.h"
#include "../Mgr/TotalMgr.h"

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
	ComboAddNumbers(ui.comboBox_dacId, 4);
	ComboAddNumbers(ui.comboBox_controlId, 4);
	ComboAddNumbers(ui.comboBox_profileId, 4);
}

void CConfigWidget::connectSignalsAndSlots()
{
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CConfigWidget::refreshAlarmButton);
	connect(ui.pushButton_servoAlarmEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.pushButton_limitEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);

	connect(ui.pushButton_loadToBoard, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);

	connect(ui.comboBox_profileId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshStopDecel(); });
	connect(ui.doubleSpinBox_smoothStopDec, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onStopDecelChanged);
	connect(ui.doubleSpinBox_smoothStopDec_2, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onStopDecelChanged);

	connect(ui.comboBox_controlId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshFollowErrorLimit(); });
	connect(ui.spinBox_followingErrorLimit, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onFollowErrorLimitChanged);

	connect(ui.comboBox_dacId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshDacValues(); });
	connect(ui.spinBox_zeroOffsetCompensation, &QAbstractSpinBox::editingFinished,	this, &CConfigWidget::onDacBiasChanged);
	connect(ui.spinBox_outputVoltageSaturationLimit, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onDacLimitChanged);
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


void CConfigWidget::onconfigChanged()
{
	refreshAlarmButton();
	refreshLimitButton();
	refreshFollowErrorLimit();
	refreshDacValues();
	refreshStopDecel();
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