#include <QTimer>

#include "GTSControllerWidget.h"

GTSControllerWidget::GTSControllerWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("GTS400");
    Init();
}

GTSControllerWidget::~GTSControllerWidget()
{}

void GTSControllerWidget::Init()
{
    QTimer::singleShot(100, this, [this]() {
        InitUI();
        InitSignalAndSlotConnect();

        });
}

void GTSControllerWidget::InitUI()
{
    m_pMainWidget = new CMainWidget(this);
    ui.stackedWidget->addWidget(m_pMainWidget);

}

void GTSControllerWidget::InitSignalAndSlotConnect()
{
}

