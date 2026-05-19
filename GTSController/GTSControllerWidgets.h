#pragma once

#include <QWidget>
#include "ui_GTSControllerWidgets.h"

class GTSControllerWidgets : public QWidget
{
	Q_OBJECT

public:
	GTSControllerWidgets(QWidget *parent = nullptr);
	~GTSControllerWidgets();

private:
	Ui::GTSControllerWidgetsClass ui;
};

