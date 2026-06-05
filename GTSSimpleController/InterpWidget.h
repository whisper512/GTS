#pragma once

#include <QWidget>
#include "ui_InterpWidget.h"

class CInterpWidget : public QWidget
{
	Q_OBJECT

public:
	CInterpWidget(QWidget *parent = nullptr);
	~CInterpWidget();

private:
	Ui::CInterpWidgetClass ui;
};

