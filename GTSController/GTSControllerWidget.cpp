#include "GTSControllerWidget.h"

GTSControllerWidget::GTSControllerWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("GTS400");
}

GTSControllerWidget::~GTSControllerWidget()
{}

