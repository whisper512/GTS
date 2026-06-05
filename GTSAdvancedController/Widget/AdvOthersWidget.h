#pragma once

#include <QWidget>
#include "ui_AdvOthersWidget.h"

class COthersWidget : public QWidget
{
	Q_OBJECT

public:
	COthersWidget(QWidget *parent = nullptr);
	~COthersWidget();

private:
	Ui::COthersWidgetClass ui;
};

