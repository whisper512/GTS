#pragma once
#include <QtWidgets/QWidget>

#include "ui_GTSControllerWidget.h"

class GTSControllerWidget : public QWidget
{
    Q_OBJECT

public:
    GTSControllerWidget(QWidget *parent = nullptr);
    ~GTSControllerWidget();

private:
    void Init();
    void InitUI();
    void InitSignalAndSlotConnect();

private:
    Ui::GTSControllerWidgetClass ui;
};

