#pragma once

#include <QWidget>
#include "ui_AdvFeedbackWidget.h"

class CFeedbackWidget : public QWidget
{
	Q_OBJECT

public:
	CFeedbackWidget(QWidget *parent = nullptr);
	~CFeedbackWidget();

private:
	Ui::CFeedbackWidgetClass ui;
};

