#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWnd.h"

class MainWnd : public QMainWindow
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = nullptr);
    ~MainWnd();

private:
    Ui::MainWndClass ui;
};

