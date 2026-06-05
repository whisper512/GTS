#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextCursor>
#include <QTime>

#include "AdvGTSControllerWidget.h"

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
        m_pTotalMgr = new CTotalMgr(this);

        InitUI();
        InitUISignalAndSlotConnect();
        InitMgrSignalAndSlotConnect();
        });
}

void GTSControllerWidget::InitUI()
{
    m_pBoardWidget = new CBoardWidget(this,this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pBoardWidget);
    m_pAxisWidget = new CAxisWidget(this, this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pAxisWidget);
    m_pInterpWidget = new CInterpWidget(this);
    ui.stackedWidget->addWidget(m_pInterpWidget);
    m_pIOWidget = new CIOWidget(this, this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pIOWidget);
    m_pFeedbackWidget = new CFeedbackWidget(this);
    ui.stackedWidget->addWidget(m_pFeedbackWidget);
    m_pConfigWidget = new CConfigWidget(this, this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pConfigWidget);
    m_pOthersWidget = new COthersWidget(this);
    ui.stackedWidget->addWidget(m_pOthersWidget);
    // 默认显示板卡页面
    ui.stackedWidget->setCurrentIndex(0);
}

void GTSControllerWidget::InitUISignalAndSlotConnect()
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

    ui.toolButton_Board->setChecked(true);
    connect(m_pBtnGroup, &QButtonGroup::idClicked, this, &GTSControllerWidget::OnBtnClicked);
}

void GTSControllerWidget::InitMgrSignalAndSlotConnect()
{
    connect(m_pTotalMgr, &CTotalMgr::boardClockUpdated, m_pBoardWidget, &CBoardWidget::onBoardClockUpdated);
    connect(m_pTotalMgr, &CTotalMgr::axisUpdated, m_pAxisWidget, &CAxisWidget::onAxisUpdated);
    connect(m_pTotalMgr, &CTotalMgr::axisSettingUpdated, m_pAxisWidget, &CAxisWidget::onAxisParamUpdated);
    connect(m_pTotalMgr, &CTotalMgr::diUpdated, m_pIOWidget, &CIOWidget::onDIUpdated);
    connect(m_pTotalMgr, &CTotalMgr::doUpdated, m_pIOWidget, &CIOWidget::onDOUpdated);
    connect(m_pTotalMgr, &CTotalMgr::configChanged,  m_pConfigWidget, &CConfigWidget::onAlarmStateChanged);

}

void GTSControllerWidget::showLog(const QString& log, QColor color)
{
    ui.plainTextEdit->moveCursor(QTextCursor::End);
    QTextCursor cursor = ui.plainTextEdit->textCursor();

    QTextCharFormat fmt;
    fmt.setForeground(color);
    QString timeStr = QTime::currentTime().toString("hh:mm:ss.zzz");
    QString fullLog = QString("[%1] %2").arg(timeStr, log);
    cursor.insertText(fullLog + "\n", fmt);
    ui.plainTextEdit->moveCursor(QTextCursor::End);
    ui.plainTextEdit->ensureCursorVisible();
}

void GTSControllerWidget::OnBtnClicked(int id)
{
    ui.stackedWidget->setCurrentIndex(id);
}
