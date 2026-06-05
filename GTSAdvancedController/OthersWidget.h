#pragma once

#include <QWidget>
#include "ui_OthersWidget.h"

class COthersWidget : public QWidget
{
	Q_OBJECT

public:
	COthersWidget(QWidget *parent = nullptr);
	~COthersWidget();

private:
	Ui::COthersWidgetClass ui;
};

