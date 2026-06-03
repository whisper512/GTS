#pragma once

#include <QMainWindow>
#include "ui_ConfigWidget.h"

class CConfigWidget : public QMainWindow
{
	Q_OBJECT

public:
	CConfigWidget(QWidget *parent = nullptr);
	~CConfigWidget();

private:
	Ui::CConfigWidgetClass ui;

private:
	void InitConfigWidget();
	void IntiUI();
	void connectSignalsAndSlots();
signals:

private slots:
public slots:


};

// 给 QComboBox 添加一组数字
inline void ComboAddNumbers(QComboBox* cb, int n)
{
	if (!cb) return;
	for (int i = 1; i <= n; ++i) {
		cb->addItem(QString::number(i));
	}
}
// 给 QComboBox 添加一组字符串
inline void ComboAddItems(QComboBox* cb, std::initializer_list<QString> items)
{
	if (!cb) return;
	for (const auto& s : items) {
		cb->addItem(s);
	}
}