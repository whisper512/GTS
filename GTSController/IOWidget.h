#pragma once

#include <QWidget>
#include "ui_IOWidget.h"

class CIOWidget : public QWidget
{
	Q_OBJECT

public:
	CIOWidget(QWidget *parent = nullptr);
	~CIOWidget();

private:
	Ui::CIOWidgetClass ui;
};

