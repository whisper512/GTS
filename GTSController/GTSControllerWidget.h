#pragma once
#include <QtWidgets/QWidget>

#include "ui_GTSControllerWidget.h"
#include "MainWidget.h"

class GTSControllerWidget : public QWidget
{
    Q_OBJECT

public:
    GTSControllerWidget(QWidget *parent = nullptr);
    ~GTSControllerWidget();

private:
    CMainWidget *m_pMainWidget = nullptr;

private:
    void Init();
    void InitUI();
    void InitSignalAndSlotConnect();



private:
    Ui::GTSControllerWidgetClass ui;
};

