#include <QTimer>
#include <QFileDialog>
#include "ConfigWidget.h"
#include "GTSControllerWidget.h"
#include "TotalMgr.h"

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
	ComboAddNumbers(ui.comboBox_encoderId, 8);
	ComboAddNumbers(ui.comboBox_controlId, 4);
	ComboAddNumbers(ui.comboBox_profileId, 4);
	ComboAddNumbers(ui.comboBox_inputID, 16);
	// 编码器当量读取有问题,屏蔽
	ui.groupBox_encoderEquivalent->setVisible(false);
}

void CConfigWidget::connectSignalsAndSlots()
{
	connect(ui.pushButton_servoAlarmEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.pushButton_limitEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.pushButton_loadToBoard, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.spinBox_profileEquivalentAlpha, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onProfileScaleChanged);
	connect(ui.spinBox_profileEquivalentBeta, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onProfileScaleChanged);
	//connect(ui.spinBox_encoderEquivalentAlpha, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onEncoderScaleChanged);
	//connect(ui.spinBox_encoderEquivalentBeta, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onEncoderScaleChanged);

	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshAlarmButton(); refreshLimitButton(); });
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshScaleEquivalents(); });
	//connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshScaleEquivalents(); });
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
	refreshScaleEquivalents();
}

void CConfigWidget::refreshAlarmButton()
{
	if (!m_pTotalMgr) {
		return;
	}
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
}

void CConfigWidget::refreshScaleEquivalents()
{
	if (!m_pTotalMgr) return;

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
}

void CConfigWidget::onProfileScaleChanged()
{
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
	if (!m_pTotalMgr) return;
	short encoder = ui.comboBox_encoderId->currentText().toShort();
	long alpha = ui.spinBox_encoderEquivalentAlpha->value();
	long beta = ui.spinBox_encoderEquivalentBeta->value();
	m_pTotalMgr->setEncoderScale(encoder, alpha, beta);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("编码器%1 当量 → α=%2 β=%3").arg(encoder).arg(alpha).arg(beta),
		Qt::darkGreen);
}
