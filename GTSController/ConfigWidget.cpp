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
}

void CConfigWidget::connectSignalsAndSlots()
{
	connect(ui.pushButton_servoAlarmEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.pushButton_limitEnable, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.pushButton_loadToBoard, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshAlarmButton(); });
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
		// TODO: 限位使能
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