#include <QTimer>
#include "ConfigWidget.h"

CConfigWidget::CConfigWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	InitConfigWidget();
}

CConfigWidget::~CConfigWidget()
{}

void CConfigWidget::InitConfigWidget()
{
	QTimer::singleShot(100, this, [this]() {
		InitAxisConfig();
		InitStepConfig();
		InitDacConfig();
		InitEncoderConfig();
		InitControlConfig();
		InitProfileConfig();
		InitDiConfig();
		InitDoConfig();
		});
	connectSignalsAndSlots();

}

void CConfigWidget::InitAxisConfig()
{
    ComboAddNumbers(ui.comboBox_axisId, 4);
    ComboAddNumbers(ui.comboBox_servoAlarmIndex, 4);
    ComboAddNumbers(ui.comboBox_PLimitIndex, 4);
    ComboAddNumbers(ui.comboBox_NLimitIndex, 4);
    ComboAddNumbers(ui.comboBox_smoothStopIndex, 16);
    ComboAddNumbers(ui.comboBox_EStopIndex, 16);
    ComboAddItems(ui.comboBox_servoAlarmType, { QStringLiteral("正限位"),QStringLiteral("负限位"), QStringLiteral("驱动报警"), QStringLiteral("原点"), QStringLiteral("通用输入") });
    ComboAddItems(ui.comboBox_PLimitType, { QStringLiteral("正限位"),QStringLiteral("负限位"), QStringLiteral("驱动报警"), QStringLiteral("原点"), QStringLiteral("通用输入") });
    ComboAddItems(ui.comboBox_NLimitType, { QStringLiteral("正限位"),QStringLiteral("负限位"), QStringLiteral("驱动报警"), QStringLiteral("原点"), QStringLiteral("通用输入") });
    ComboAddItems(ui.comboBox_smoothStopType, { QStringLiteral("正限位"),QStringLiteral("负限位"), QStringLiteral("驱动报警"), QStringLiteral("原点"), QStringLiteral("通用输入") });
    ComboAddItems(ui.comboBox_EStopType, { QStringLiteral("正限位"),QStringLiteral("负限位"), QStringLiteral("驱动报警"), QStringLiteral("原点"), QStringLiteral("通用输入") });
}

void CConfigWidget::InitStepConfig()
{
	ComboAddNumbers(ui.comboBox_stepIndex, 4);
	ComboAddItems(ui.comboBox_pulseOutputMode, { QStringLiteral("脉冲+方向"), QStringLiteral("CCW/CW") });
}

void CConfigWidget::InitDacConfig()
{
	ComboAddNumbers(ui.comboBox_dacIndex, 12);
	ComboAddItems(ui.comboBox_associationControl, { QStringLiteral("None"), QStringLiteral("1"),QStringLiteral("2"),QStringLiteral("3"),QStringLiteral("4") });
	ComboAddItems(ui.comboBox_outputVoltageReversal, { QStringLiteral("正常"), QStringLiteral("取反") });
}

void CConfigWidget::InitEncoderConfig()
{
	ComboAddNumbers(ui.comboBox_encoderIndex, 11);
	ComboAddItems(ui.comboBox_inputPulseInvert, { QStringLiteral("正常"), QStringLiteral("取反") });
	ComboAddItems(ui.comboBox_pulseCountSource, { QStringLiteral("编码器"), QStringLiteral("脉冲计数器") });
	ComboAddItems(ui.comboBox_homeCaptureTriggerEdge, { QStringLiteral("下降沿"), QStringLiteral("上升沿") });
	ComboAddItems(ui.comboBox_indexCaptureTriggerEdge, { QStringLiteral("下降沿"), QStringLiteral("上升沿") });
}

void CConfigWidget::InitControlConfig()
{
	ComboAddNumbers(ui.comboBox_controlIndex, 4);
	ComboAddItems(ui.comboBox_associatedAxis, { QStringLiteral("None"),QStringLiteral("1"), QStringLiteral("2"), QStringLiteral("3"), QStringLiteral("4"),
		QStringLiteral("5"), QStringLiteral("6"), QStringLiteral("7"), QStringLiteral("8") });
	ComboAddItems(ui.comboBox_associatedEncoder, { QStringLiteral("None"),QStringLiteral("1"), QStringLiteral("2"), QStringLiteral("3"), QStringLiteral("4"),
		QStringLiteral("5"), QStringLiteral("6"), QStringLiteral("7"), QStringLiteral("8"),QStringLiteral("9"),QStringLiteral("10"),QStringLiteral("11") });
}

void CConfigWidget::InitProfileConfig()
{
	ComboAddNumbers(ui.comboBox_profileIndex, 4);
}

void CConfigWidget::InitDiConfig()
{
	ComboAddItems(ui.comboBox_diType, { QStringLiteral("正限位"), QStringLiteral("负限位"), QStringLiteral("驱动报警"),
		 QStringLiteral("原点"),  QStringLiteral("通用输入"),  QStringLiteral("电机到位"),  QStringLiteral("手轮")});
	ComboAddNumbers(ui.comboBox_diIndex, 8);
	ComboAddItems(ui.comboBox_inputInvert, { QStringLiteral("正常"), QStringLiteral("取反") });
}

void CConfigWidget::InitDoConfig()
{
	ComboAddItems(ui.comboBox_doType, { QStringLiteral("伺服使能"), QStringLiteral("清除报警"), QStringLiteral("通用输出") });
	ComboAddNumbers(ui.comboBox_doIndex, 8);
	ComboAddItems(ui.comboBox_outputInvert, { QStringLiteral("正常"), QStringLiteral("取反") });
	ComboAddItems(ui.comboBox_doAssociatedAxis, { QStringLiteral("None"),QStringLiteral("1"), QStringLiteral("2"), QStringLiteral("3"), QStringLiteral("4"),
		QStringLiteral("5"), QStringLiteral("6"), QStringLiteral("7"), QStringLiteral("8") });
}

void CConfigWidget::connectSignalsAndSlots()
{
    // 按钮
    connect(ui.pushButton_loadFromFile, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
    connect(ui.pushButton_writeToFile, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
    connect(ui.pushButton_readControlState, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);
    connect(ui.pushButton_writeControlState, &QPushButton::clicked, this, &CConfigWidget::onBtnClicked);

    // tab_axis
    {
        QComboBox* combos[] = {
            ui.comboBox_axisId,
            ui.comboBox_servoAlarmType, ui.comboBox_servoAlarmIndex,
            ui.comboBox_PLimitType,     ui.comboBox_PLimitIndex,
            ui.comboBox_NLimitType,     ui.comboBox_NLimitIndex,
            ui.comboBox_smoothStopType, ui.comboBox_smoothStopIndex,
            ui.comboBox_EStopType,      ui.comboBox_EStopIndex
        };
        for (auto* cb : combos)
            connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CConfigWidget::onAxisCfgChanged);

        connect(ui.checkBox_axisActivate, &QCheckBox::toggled,
            this, &CConfigWidget::onAxisCfgChanged);

        QAbstractSpinBox* spins[] = {
            ui.spinBox_profileEquivalentAlpha, ui.spinBox_profileEquivalentBeta,
            ui.spinBox_encoderEquivalentAlpha, ui.spinBox_encoderEquivalentBeta
        };
        for (auto* sp : spins)
            connect(sp, &QAbstractSpinBox::editingFinished,
                this, &CConfigWidget::onAxisCfgChanged);
    }

    // tab_step
    {
        QComboBox* combos[] = { ui.comboBox_stepIndex, ui.comboBox_pulseOutputMode };
        for (auto* cb : combos)
            connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CConfigWidget::onStepCfgChanged);

        connect(ui.checkBox_stepActivate, &QCheckBox::toggled,
            this, &CConfigWidget::onStepCfgChanged);
    }

    // tab_dac
    {
        QComboBox* combos[] = { ui.comboBox_dacIndex, ui.comboBox_outputVoltageReversal,
                                ui.comboBox_associationControl };
        for (auto* cb : combos)
            connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CConfigWidget::onDacCfgChanged);

        connect(ui.checkBox_dacActivate, &QCheckBox::toggled,
            this, &CConfigWidget::onDacCfgChanged);

        QAbstractSpinBox* spins[] = { ui.spinBox_zeroOffsetCompensation,
                                      ui.spinBox_outputVoltageSaturationLimit };
        for (auto* sp : spins)
            connect(sp, &QAbstractSpinBox::editingFinished,
                this, &CConfigWidget::onDacCfgChanged);
    }

    // tab_encoder
    {
        QComboBox* combos[] = {
            ui.comboBox_encoderIndex,        ui.comboBox_inputPulseInvert,
            ui.comboBox_pulseCountSource,    ui.comboBox_homeCaptureTriggerEdge,
            ui.comboBox_indexCaptureTriggerEdge
        };
        for (auto* cb : combos)
            connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CConfigWidget::onEncoderCfgChanged);

        connect(ui.checkBox_encoderActivate, &QCheckBox::toggled,
            this, &CConfigWidget::onEncoderCfgChanged);
    }

    // tab_control
    {
        QComboBox* combos[] = {
            ui.comboBox_controlIndex, ui.comboBox_associatedAxis,
            ui.comboBox_associatedEncoder
        };
        for (auto* cb : combos)
            connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CConfigWidget::onControlCfgChanged);

        connect(ui.spinBox_followingErrorLimit, &QAbstractSpinBox::editingFinished,
            this, &CConfigWidget::onControlCfgChanged);
    }

    // tab_profile
    {
        connect(ui.comboBox_profileIndex, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CConfigWidget::onProfileCfgChanged);

        connect(ui.checkBox_proflieActivate, &QCheckBox::toggled,
            this, &CConfigWidget::onProfileCfgChanged);

        QAbstractSpinBox* spins[] = { ui.doubleSpinBox_smoothStopDec, ui.doubleSpinBox_EStopDec };
        for (auto* sp : spins)
            connect(sp, &QAbstractSpinBox::editingFinished,
                this, &CConfigWidget::onProfileCfgChanged);
    }

    // tab_di
    {
        QComboBox* combos[] = { ui.comboBox_diType, ui.comboBox_diIndex,
                                ui.comboBox_inputInvert };
        for (auto* cb : combos)
            connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CConfigWidget::onDICfgChanged);

        connect(ui.checkBox_diActivate, &QCheckBox::toggled,
            this, &CConfigWidget::onDICfgChanged);

        connect(ui.spinBox_filterTime, &QAbstractSpinBox::editingFinished,
            this, &CConfigWidget::onDICfgChanged);
    }

    // tab_do
    {
        QComboBox* combos[] = {
            ui.comboBox_doType, ui.comboBox_doIndex,
            ui.comboBox_outputInvert, ui.comboBox_doAssociatedAxis
        };
        for (auto* cb : combos)
            connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &CConfigWidget::onDOCfgChanged);

        connect(ui.checkBox_doActivate, &QCheckBox::toggled,
            this, &CConfigWidget::onDOCfgChanged);
    }
}


void CConfigWidget::onBtnClicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;

	QString objName = btn->objectName();

	if (objName == "pushButton_loadFromFile") {
		// TODO: 从配置文件加载
	}
	else if (objName == "pushButton_writeToFile") {
		// TODO: 写入到配置文件
	}
	else if (objName == "pushButton_readControlState") {
		// TODO: 从板卡读取当前配置
	}
	else if (objName == "pushButton_writeControlState") {
		// TODO: 将配置写入板卡
	}
}

void CConfigWidget::onAxisCfgChanged()
{
    QObject* senderObj = sender();
    if (!senderObj) return;
    QString objName = senderObj->objectName();
    if (objName == "comboBox_axisId") {
        // TODO: 轴 ID 变更
    }
    else if (objName == "checkBox_axisActivate") {
        // TODO: 轴激活状态变更
    }
    else if (objName == "comboBox_servoAlarmType") {
        // TODO: 伺服报警信号类型变更
    }
    else if (objName == "comboBox_servoAlarmIndex") {
        // TODO: 伺服报警信号索引变更
    }
    else if (objName == "comboBox_PLimitType") {
        // TODO: 正限位信号类型变更
    }
    else if (objName == "comboBox_PLimitIndex") {
        // TODO: 正限位信号索引变更
    }
    else if (objName == "comboBox_NLimitType") {
        // TODO: 负限位信号类型变更
    }
    else if (objName == "comboBox_NLimitIndex") {
        // TODO: 负限位信号索引变更
    }
    else if (objName == "comboBox_smoothStopType") {
        // TODO: 平滑停止信号类型变更
    }
    else if (objName == "comboBox_smoothStopIndex") {
        // TODO: 平滑停止信号索引变更
    }
    else if (objName == "comboBox_EStopType") {
        // TODO: 急停信号类型变更
    }
    else if (objName == "comboBox_EStopIndex") {
        // TODO: 急停信号索引变更
    }
    else if (objName == "spinBox_profileEquivalentAlpha") {
        // TODO: profile 当量分子变更
    }
    else if (objName == "spinBox_profileEquivalentBeta") {
        // TODO: profile 当量分母变更
    }
    else if (objName == "spinBox_encoderEquivalentAlpha") {
        // TODO: encoder 当量分子变更
    }
    else if (objName == "spinBox_encoderEquivalentBeta") {
        // TODO: encoder 当量分母变更
    }
}

void CConfigWidget::onStepCfgChanged()
{
    QString objName = sender()->objectName();

    if (objName == "comboBox_stepIndex") {
        // TODO:
    }
    else if (objName == "comboBox_pulseOutputMode") {
        // TODO:
    }
    else if (objName == "checkBox_stepActivate") {
        // TODO:
    }
}

void CConfigWidget::onDacCfgChanged()
{
    QString objName = sender()->objectName();

    if (objName == "comboBox_dacIndex") {
        // TODO:
    }
    else if (objName == "comboBox_outputVoltageReversal") {
        // TODO:
    }
    else if (objName == "comboBox_associationControl") {
        // TODO:
    }
    else if (objName == "checkBox_dacActivate") {
        // TODO:
    }
    else if (objName == "spinBox_zeroOffsetCompensation") {
        // TODO:
    }
    else if (objName == "spinBox_outputVoltageSaturationLimit") {
        // TODO:
    }
}

void CConfigWidget::onEncoderCfgChanged()
{
    QString objName = sender()->objectName();

    if (objName == "comboBox_encoderIndex") {
        // TODO:
    }
    else if (objName == "comboBox_inputPulseInvert") {
        // TODO:
    }
    else if (objName == "comboBox_pulseCountSource") {
        // TODO:
    }
    else if (objName == "comboBox_homeCaptureTriggerEdge") {
        // TODO:
    }
    else if (objName == "comboBox_indexCaptureTriggerEdge") {
        // TODO:
    }
    else if (objName == "checkBox_encoderActivate") {
        // TODO:
    }
}

void CConfigWidget::onControlCfgChanged()
{
    QString objName = sender()->objectName();

    if (objName == "comboBox_controlIndex") {
        // TODO:
    }
    else if (objName == "comboBox_associatedAxis") {
        // TODO:
    }
    else if (objName == "comboBox_associatedEncoder") {
        // TODO:
    }
    else if (objName == "spinBox_followingErrorLimit") {
        // TODO:
    }
}

void CConfigWidget::onProfileCfgChanged()
{
    QString objName = sender()->objectName();

    if (objName == "comboBox_profileIndex") {
        // TODO:
    }
    else if (objName == "checkBox_proflieActivate") {
        // TODO:
    }
    else if (objName == "doubleSpinBox_smoothStopDec") {
        // TODO:
    }
    else if (objName == "doubleSpinBox_EStopDec") {
        // TODO:
    }
}

void CConfigWidget::onDICfgChanged()
{
    QString objName = sender()->objectName();

    if (objName == "comboBox_diType") {
        // TODO:
    }
    else if (objName == "comboBox_diIndex") {
        // TODO:
    }
    else if (objName == "comboBox_inputInvert") {
        // TODO:
    }
    else if (objName == "checkBox_diActivate") {
        // TODO:
    }
    else if (objName == "spinBox_filterTime") {
        // TODO:
    }
}

void CConfigWidget::onDOCfgChanged()
{
    QString objName = sender()->objectName();

    if (objName == "comboBox_doType") {
        // TODO:
    }
    else if (objName == "comboBox_doIndex") {
        // TODO:
    }
    else if (objName == "comboBox_outputInvert") {
        // TODO:
    }
    else if (objName == "comboBox_doAssociatedAxis") {
        // TODO:
    }
    else if (objName == "checkBox_doActivate") {
        // TODO:
    }
}
