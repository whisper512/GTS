#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>

#include "GTSControllerWidget.h"

GTSControllerWidget::GTSControllerWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("GTS400");
    Init();
}

GTSControllerWidget::~GTSControllerWidget()
{
}

void GTSControllerWidget::Init()
{
    QTimer::singleShot(100, this, [this]() {
        InitUI();
        InitSignalAndSlotConnect();
        });
}

void GTSControllerWidget::InitUI()
{
    
    m_pBoardWidget = new CBoardWidget(this);
    ui.stackedWidget->addWidget(m_pBoardWidget);
    m_pAxisWidget = new CAxisWidget(this);
    ui.stackedWidget->addWidget(m_pAxisWidget);
    m_pInterpWidget = new CInterpWidget(this);
    ui.stackedWidget->addWidget(m_pInterpWidget);
    m_pIOWidget = new CIOWidget(this);
    ui.stackedWidget->addWidget(m_pIOWidget);
    m_pFeedbackWidget = new CFeedbackWidget(this);
    ui.stackedWidget->addWidget(m_pFeedbackWidget);
    m_pConfigWidget = new CConfigWidget(this);
    ui.stackedWidget->addWidget(m_pConfigWidget);
    m_pOthersWidget = new COthersWidget(this);
    ui.stackedWidget->addWidget(m_pOthersWidget);
    // 默认显示板卡页面
    ui.stackedWidget->setCurrentIndex(0);
}

void GTSControllerWidget::InitSignalAndSlotConnect()
{
    ui.toolButton_Board->setCheckable(true);
    ui.toolButton_Axis->setCheckable(true);
    ui.toolButton_Interpolation->setCheckable(true);
    ui.toolButton_IO->setCheckable(true);
    ui.toolButton_Feedback->setCheckable(true);
    ui.toolButton_Config->setCheckable(true);
    ui.toolButton_Others->setCheckable(true);

    
    m_pBtnGroup = new QButtonGroup(this);
    m_pBtnGroup->addButton(ui.toolButton_Board, 0);
    m_pBtnGroup->addButton(ui.toolButton_Axis, 1);
    m_pBtnGroup->addButton(ui.toolButton_Interpolation, 2);
    m_pBtnGroup->addButton(ui.toolButton_IO, 3);
    m_pBtnGroup->addButton(ui.toolButton_Feedback, 4);
    m_pBtnGroup->addButton(ui.toolButton_Config, 5);
    m_pBtnGroup->addButton(ui.toolButton_Others, 6);

    // 默认
    ui.toolButton_Board->setChecked(true);
    connect(m_pBtnGroup, &QButtonGroup::idClicked, this, &GTSControllerWidget::OnBtnClicked);
}

void GTSControllerWidget::OnBtnClicked(int id)
{
    ui.stackedWidget->setCurrentIndex(id);
}
