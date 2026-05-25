#pragma once

#include <QWidget>
#include "ui_AxisWidget.h"

class CAxisWidget : public QWidget
{
	Q_OBJECT

public:
	CAxisWidget(QWidget *parent = nullptr);
	~CAxisWidget();

private:
	Ui::CAxisWidgetClass ui;
};

