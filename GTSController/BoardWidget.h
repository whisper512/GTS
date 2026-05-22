#pragma once

#include <QWidget>
#include "ui_BoardWidget.h"

class CBoardWidget : public QWidget
{
	Q_OBJECT

public:
	CBoardWidget(QWidget *parent = nullptr);
	~CBoardWidget();

private:
	Ui::BoardWidgetClass ui;
};

