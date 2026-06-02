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

