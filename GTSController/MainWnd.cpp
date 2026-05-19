#include "MainWnd.h"

MainWnd::MainWnd(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowIcon(QIcon(":/MainWnd/res/owl.png"));
}

MainWnd::~MainWnd()
{}

