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
		connectSignalsAndSlots();
		});
}

void CConfigWidget::InitUI()
{
	ComboAddNumbers(ui.comboBox_axisId, 4);
	ComboAddNumbers(ui.comboBox_dacId, 4);
	ComboAddNumbers(ui.comboBox_controlId, 4);
	ComboAddNumbers(ui.comboBox_profileId, 4);
	ComboAddItems(ui.comboBox_controlMode, {
		QStringLiteral("闭环"),
		QStringLiteral("开环"),
		QStringLiteral("调试")
		});

	ComboAddItems(ui.comboBox_homeMode, {
		QStringLiteral("负限位回零"),
		});
	ComboAddNumbers(ui.comboBox_axisIdHomeConfig, 4);
}

void CConfigWidget::connectSignalsAndSlots()
{
	connect(ui.pushButton_loadToBoard, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
	connect(ui.comboBox_profileId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshStopDecel(); });
	connect(ui.doubleSpinBox_smoothStopDec, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onStopDecelChanged);
	connect(ui.doubleSpinBox_smoothStopDec_2, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onStopDecelChanged);
	connect(ui.comboBox_controlId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshFollowErrorLimit(); });
	connect(ui.spinBox_followingErrorLimit, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onFollowErrorLimitChanged);
	connect(ui.comboBox_dacId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshDacValues(); });
	connect(ui.spinBox_zeroOffsetCompensation, &QAbstractSpinBox::editingFinished,	this, &CConfigWidget::onDacBiasChanged);
	connect(ui.spinBox_outputVoltageSaturationLimit, &QAbstractSpinBox::editingFinished,this, &CConfigWidget::onDacLimitChanged);
	// ===== 轴切换刷新  =====
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this]() { refreshScaleValues(); });
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),	this, [this]() { refreshControlMode(); });
	// ===== 当量：spinBox 修改后保存 JSON + 写板卡 =====
	connect(ui.spinBox_prfAlpha, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onPrfAlphaChanged);
	connect(ui.spinBox_prfBeta, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onPrfBetaChanged);
	connect(ui.spinBox_encAlpha, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onEncAlphaChanged);
	connect(ui.spinBox_encBeta, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onEncBetaChanged);
	connect(ui.comboBox_controlMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CConfigWidget::onControlModeChanged);
	// ===== 回零参数:轴切换刷新 =====
	connect(ui.comboBox_axisIdHomeConfig, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshHomeConfig(); });
	// ===== 回零参数:控件修改后保存 JSON =====
	connect(ui.comboBox_homeMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CConfigWidget::onHomeModeChanged);
	connect(ui.doubleSpinBox_homeVel, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onHomeVelChanged);
	connect(ui.doubleSpinBox_homeAcc, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onHomeAccChanged);
	connect(ui.doubleSpinBox_homeRange, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onHomeRangeChanged);
	connect(ui.doubleSpinBox_homeOffset, &QAbstractSpinBox::editingFinished, this, &CConfigWidget::onHomeOffsetChanged);
	// ===== 轴限位：轴切换刷新 =====
	connect(ui.comboBox_axisId, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, [this]() { refreshAxisLimit(); });
	// ===== 轴限位：spinBox 修改后保存 JSON =====
	connect(ui.spinBox_pLimit, &QAbstractSpinBox::editingFinished,
		this, &CConfigWidget::onPosLimitChanged);
	connect(ui.spinBox_nLimit, &QAbstractSpinBox::editingFinished,
		this, &CConfigWidget::onNegLimitChanged);

}

void CConfigWidget::onBtnClicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;

	QString objName = btn->objectName();

	if (objName == "pushButton_loadToBoard") {
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


void CConfigWidget::onconfigChanged()
{
	refreshFollowErrorLimit();
	refreshDacValues();
	refreshStopDecel();
	refreshScaleValues();
	refreshControlMode();
	refreshHomeConfig();
	refreshAxisLimit();
}



void CConfigWidget::refreshDacValues()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short dac = ui.comboBox_dacId->currentText().toShort();

	ui.spinBox_zeroOffsetCompensation->setValue(
		(int)m_pTotalMgr->configMgr()->dacBias(dac));
	ui.spinBox_outputVoltageSaturationLimit->setValue(
		(int)m_pTotalMgr->configMgr()->dacLimit(dac));
	m_bRefreshing = false;
}

void CConfigWidget::onDacBiasChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short dac = ui.comboBox_dacId->currentText().toShort();
	short bias = (short)ui.spinBox_zeroOffsetCompensation->value();
	m_pTotalMgr->configMgr()->setDacBias(dac, bias);

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
	m_pTotalMgr->configMgr()->setDacLimit(dac, limit);

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
		(int)m_pTotalMgr->configMgr()->followErrorLimit(ctrl));
	m_bRefreshing = false;
}

void CConfigWidget::onFollowErrorLimitChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short ctrl = ui.comboBox_controlId->currentText().toShort();
	long error = ui.spinBox_followingErrorLimit->value();
	m_pTotalMgr->configMgr()->setFollowErrorLimit(ctrl, error);

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
		m_pTotalMgr->configMgr()->smoothStopDec(profile));
	ui.doubleSpinBox_smoothStopDec_2->setValue(
		m_pTotalMgr->configMgr()->estopDec(profile));
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

	m_pTotalMgr->configMgr()->setStopDecel(profile, smooth, abrupt);

	m_pGTSControllerWidget->showLog(
		QStringLiteral("Profile%1 停止减速度 → 平滑=%2 急停=%3")
		.arg(profile).arg(smooth, 0, 'f', 3).arg(abrupt, 0, 'f', 3),
		Qt::darkGreen);
}


void CConfigWidget::refreshScaleValues()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short axis = ui.comboBox_axisId->currentText().toShort();

	ui.spinBox_prfAlpha->setValue((int)m_pTotalMgr->configMgr()->profileScaleAlpha(axis));
	ui.spinBox_prfBeta->setValue((int)m_pTotalMgr->configMgr()->profileScaleBeta(axis));
	ui.spinBox_encAlpha->setValue((int)m_pTotalMgr->configMgr()->encoderScaleAlpha(axis));
	ui.spinBox_encBeta->setValue((int)m_pTotalMgr->configMgr()->encoderScaleBeta(axis));

	m_bRefreshing = false;
}

void CConfigWidget::onPrfAlphaChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	long  alpha = ui.spinBox_prfAlpha->value();
	long  beta = ui.spinBox_prfBeta->value();

	m_pTotalMgr->configMgr()->setProfileScale(axis, alpha, beta);
	m_pTotalMgr->configMgr()->saveAxisConfig();
	
	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 profile当量 → alpha=%2 beta=%3").arg(axis).arg(alpha).arg(beta),
		Qt::darkGreen);
}

void CConfigWidget::onPrfBetaChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	long  alpha = ui.spinBox_prfAlpha->value();
	long  beta = ui.spinBox_prfBeta->value();

	m_pTotalMgr->configMgr()->setProfileScale(axis, alpha, beta);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 profile当量 → alpha=%2 beta=%3").arg(axis).arg(alpha).arg(beta),
		Qt::darkGreen);
}

void CConfigWidget::onEncAlphaChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	long  alpha = ui.spinBox_encAlpha->value();
	long  beta = ui.spinBox_encBeta->value();

	m_pTotalMgr->configMgr()->setEncoderScale(axis, alpha, beta);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 encoder当量 → alpha=%2 beta=%3").arg(axis).arg(alpha).arg(beta),
		Qt::darkGreen);
}

void CConfigWidget::onEncBetaChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	long  alpha = ui.spinBox_encAlpha->value();
	long  beta = ui.spinBox_encBeta->value();

	m_pTotalMgr->configMgr()->setEncoderScale(axis, alpha, beta);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 encoder当量 → alpha=%2 beta=%3").arg(axis).arg(alpha).arg(beta),
		Qt::darkGreen);
}

void CConfigWidget::refreshControlMode()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;

	short axis = ui.comboBox_axisId->currentText().toShort();
	int  mode = static_cast<int>(m_pTotalMgr->configMgr()->controlMode(axis));
	ui.comboBox_controlMode->setCurrentIndex(mode);

	m_bRefreshing = false;
}

void CConfigWidget::onControlModeChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;
	if (!m_pTotalMgr->boardMgr()->isOpen()) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	int  index = ui.comboBox_controlMode->currentIndex();
	auto mode = static_cast<ControlMode>(index);

	m_pTotalMgr->configMgr()->setControlMode(axis, mode);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	// 用 QStringLiteral 数组
	static const QString modeNames[] = {
		QStringLiteral("闭环"),
		QStringLiteral("开环"),
		QStringLiteral("调试")
	};

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 控制模式 → %2").arg(axis).arg(modeNames[index]),
		Qt::darkGreen);
}

// ============================================================
// 回零参数
// ============================================================

void CConfigWidget::refreshHomeConfig()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short axis = ui.comboBox_axisIdHomeConfig->currentText().toShort();

	int mode = static_cast<int>(m_pTotalMgr->configMgr()->homeModeValue(axis));
	ui.comboBox_homeMode->setCurrentIndex(mode);
	ui.doubleSpinBox_homeVel->setValue(m_pTotalMgr->configMgr()->homeVel(axis));
	ui.doubleSpinBox_homeAcc->setValue(m_pTotalMgr->configMgr()->homeAcc(axis));
	ui.doubleSpinBox_homeRange->setValue(m_pTotalMgr->configMgr()->homeRange(axis));
	ui.doubleSpinBox_homeOffset->setValue(m_pTotalMgr->configMgr()->homeOffset(axis));

	m_bRefreshing = false;
}

void CConfigWidget::onHomeModeChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;

	short axis = ui.comboBox_axisIdHomeConfig->currentText().toShort();
	int  index = ui.comboBox_homeMode->currentIndex();
	auto mode = static_cast<homeMode>(index);

	m_pTotalMgr->configMgr()->setHomeMode(axis, mode);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	static const QString modeNames[] = {
		QStringLiteral("负限位回零"),
	};
	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 回零模式 → %2").arg(axis).arg(modeNames[index]),
		Qt::darkGreen);
}

void CConfigWidget::onHomeVelChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;

	short  axis = ui.comboBox_axisIdHomeConfig->currentText().toShort();
	double vel = ui.doubleSpinBox_homeVel->value();

	m_pTotalMgr->configMgr()->setHomeVel(axis, vel);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 回零速度 → %2 mm/s").arg(axis).arg(vel, 0, 'f', 2),
		Qt::darkGreen);
}

void CConfigWidget::onHomeAccChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;

	short  axis = ui.comboBox_axisIdHomeConfig->currentText().toShort();
	double acc = ui.doubleSpinBox_homeAcc->value();

	m_pTotalMgr->configMgr()->setHomeAcc(axis, acc);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 回零加速度 → %2 mm/s^2").arg(axis).arg(acc, 0, 'f', 2),
		Qt::darkGreen);
}

void CConfigWidget::onHomeRangeChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;

	short  axis = ui.comboBox_axisIdHomeConfig->currentText().toShort();
	double range = ui.doubleSpinBox_homeRange->value();

	m_pTotalMgr->configMgr()->setHomeRange(axis, range);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 搜索范围 → %2 mm").arg(axis).arg(range, 0, 'f', 2),
		Qt::darkGreen);
}

void CConfigWidget::onHomeOffsetChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;

	short  axis = ui.comboBox_axisIdHomeConfig->currentText().toShort();
	double offset = ui.doubleSpinBox_homeOffset->value();

	m_pTotalMgr->configMgr()->setHomeOffset(axis, offset);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 回零偏移 → %2 mm").arg(axis).arg(offset, 0, 'f', 3),
		Qt::darkGreen);
}

// ============================================================
// 轴限位
// ============================================================

void CConfigWidget::refreshAxisLimit()
{
	if (!m_pTotalMgr) return;
	m_bRefreshing = true;
	short axis = ui.comboBox_axisId->currentText().toShort();

	ui.spinBox_pLimit->setValue((int)m_pTotalMgr->configMgr()->posLimit(axis));
	ui.spinBox_nLimit->setValue((int)m_pTotalMgr->configMgr()->negLimit(axis));

	m_bRefreshing = false;
}

void CConfigWidget::onPosLimitChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	double limit = ui.spinBox_pLimit->value();

	m_pTotalMgr->configMgr()->setPosLimit(axis, limit);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 正限位 → %2").arg(axis).arg(limit, 0, 'f', 1),
		Qt::darkGreen);
}

void CConfigWidget::onNegLimitChanged()
{
	if (m_bRefreshing) return;
	if (!m_pTotalMgr) return;

	short axis = ui.comboBox_axisId->currentText().toShort();
	double limit = ui.spinBox_nLimit->value();

	m_pTotalMgr->configMgr()->setNegLimit(axis, limit);
	m_pTotalMgr->configMgr()->saveAxisConfig();

	m_pGTSControllerWidget->showLog(
		QStringLiteral("轴%1 负限位 → %2").arg(axis).arg(limit, 0, 'f', 1),
		Qt::darkGreen);
}
