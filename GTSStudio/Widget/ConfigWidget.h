#pragma once

#include <QWidget>
#include "ui_ConfigWidget.h"

class GtsMgr;

class ConfigWidget : public QWidget
{
	Q_OBJECT

public:
	ConfigWidget(QWidget* parent = nullptr);
	~ConfigWidget();
	void setGtsTotalMgr(GtsMgr* mgr);

private:
	void initUI();
	void connectSignals();
	// refresh
	void refreshDacValues();
	void refreshFollowErrorLimit();
	void refreshStopDecel();
	void refreshScaleValues();
	void refreshControlMode();
	void refreshHomeConfig();
	void refreshAxisLimit();
	void refreshAxisName();
	void refreshSoftPulseScale();
	void refreshCoordCfg();
	// commit
	void commitDacForAxis(short dac);
	void commitFollowErrorForAxis(short ctrl);
	void commitStopDecelForProfile(short profile);
	void commitScaleForAxis(short axis);
	void commitControlModeForAxis(short axis);
	void commitHomeForAxis(short axis);
	void commitAxisLimitForAxis(short axis);
	void commitAxisNameForAxis(short axis);
	void commitSoftPulseScaleForAxis(short axis);
	void commitCoordCfg();

private:
	Ui::CConfigWidgetClass ui;
	GtsMgr* m_gtsMgr = nullptr;
	bool m_refreshing = false;
	short m_prevDacId = 1;
	short m_prevCtrlId = 1;
	short m_prevProfileId = 1;
	short m_prevAxisId = 1;
	short m_prevHomeAxisId = 1;

private slots:
	void onApplyAndSave();
	void onApplyToBoard();
	void onLoadConfigFile();

public slots:
	void onConfigChanged();
};

inline void comboAddNumbers(QComboBox* cb, int n)
{
	if (!cb) return;
	for (int i = 1; i <= n; ++i)
		cb->addItem(QString::number(i));
}

inline void comboAddItems(QComboBox* cb, std::initializer_list<QString> items)
{
	if (!cb) return;
	for (const auto& s : items)
		cb->addItem(s);
}
