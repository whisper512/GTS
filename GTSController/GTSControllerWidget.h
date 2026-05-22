#pragma once
#include <QtWidgets/QWidget>

#include "ui_GTSControllerWidget.h"
#include "BoardWidget.h"

class GTSControllerWidget : public QWidget
{
    Q_OBJECT

public:
    GTSControllerWidget(QWidget *parent = nullptr);
    ~GTSControllerWidget();

private:
    CBoardWidget *m_pMainWidget = nullptr;

private:
    void Init();
    void InitUI();
    void InitSignalAndSlotConnect();



private:
    Ui::GTSControllerWidgetClass ui;
};

