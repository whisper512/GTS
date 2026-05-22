#pragma once

#include <QWidget>
#include "ui_MainWidget.h"

class CMainWidget : public QWidget
{
	Q_OBJECT

public:
	CMainWidget(QWidget *parent = nullptr);
	~CMainWidget();

private:
	Ui::CMainWidgetClass ui;
};

