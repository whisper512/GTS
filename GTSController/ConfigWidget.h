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
};

