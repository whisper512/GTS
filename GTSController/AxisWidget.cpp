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
	connect(ui.pushButton_ActMotion, &QPushButton::clicked, this, &CAxisWidget::onBtnClick);
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

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 运动触发（待实现）").arg(m_iAxisId), Qt::blue);
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

void CAxisWidget::onComboBoxCurrentIndexChanged(int index)
{
	m_iAxisId = index + 1;  

	if (m_pTotalMgr && m_pTotalMgr->boardMgr()->isOpen()) {
	}
}

void CAxisWidget::onAxisUpdated(const std::vector<stuAxis>& axisInfo)
{
	int index = m_iAxisId - 1;
	if (index < 0 || index >= (int)axisInfo.size()) return;
	stuAxis axis = axisInfo[index];

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

	if (axis.bServoOn)
	{
        ui.pushButton_sevorOn->setText(QStringLiteral("失能"));
	}
	else 
	{
		ui.pushButton_sevorOn->setText(QStringLiteral("使能"));
	}


	//QString statusStr = QStringLiteral(
	//	"轴%1 | 位置:%2 | 速度:%3 | 加速度:%4 | "
	//	"使能:%5 | 报警:%6 | 运动:%7 | 正限位:%8 | 负限位:%9 | "
	//	"误差:%10 | 急停:%11 | 平滑停止:%12")
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
	//	.arg(axis.bSmoothStop ? QStringLiteral("是") : QStringLiteral("否"));
	//m_pGTSControllerWidget->showLog(statusStr, Qt::darkCyan);
}
