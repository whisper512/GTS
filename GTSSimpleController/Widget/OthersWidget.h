#pragma once

#include <QWidget>
#include "ui_OthersWidget.h"

class OthersWidget : public QWidget
{
	Q_OBJECT

public:
	OthersWidget(QWidget *parent = nullptr);
	~OthersWidget();

private:
	Ui::COthersWidgetClass ui;
};

