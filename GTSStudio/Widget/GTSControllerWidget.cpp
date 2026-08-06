#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextCursor>
#include <QTime>

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
    m_bIsShuttingDown = true;

    if (m_pTotalMgr)
    {
        m_pTotalMgr->disconnect();
    }

    if (m_pBoardWidget)
    {
        delete m_pBoardWidget;
        m_pBoardWidget = nullptr;
    }
    if (m_pMasterControlWidget)
    {
        delete m_pMasterControlWidget;
        m_pMasterControlWidget = nullptr;
    }
    if (m_pAxisWidget)
    {
        delete m_pAxisWidget;
        m_pAxisWidget = nullptr;
    }
    if (m_pIOWidget)
    {
        delete m_pIOWidget;
        m_pIOWidget = nullptr;
    }
    if (m_pConfigWidget)
    {
        delete m_pConfigWidget;
        m_pConfigWidget = nullptr;
    }
    if (m_pOthersWidget)
    {
        delete m_pOthersWidget;
        m_pOthersWidget = nullptr;
    }

    m_pTotalMgr = nullptr;
}

void GTSControllerWidget::Init()
{
    QTimer::singleShot(100, this, [this]() {
        m_pTotalMgr = new GtsMgr(this);

        InitUI();
        InitUISignalAndSlotConnect();
        InitMgrSignalAndSlotConnect();
        // 初始化读取配置
        m_pTotalMgr->configMgr()->loadIODescriptions();
        m_pTotalMgr->configMgr()->loadAxisConfig();
        emit m_pTotalMgr->configMgr()->configChanged();
        });
}

void GTSControllerWidget::InitUI()
{
    m_pBoardWidget = new BoardWidget(this);
    m_pBoardWidget->setGtsTotalMgr(this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pBoardWidget);
    m_pMasterControlWidget = new MasterControlWidget(this);
    m_pMasterControlWidget->setGtsTotalMgr(this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pMasterControlWidget);
    m_pAxisWidget = new AxisWidget(this);
    m_pAxisWidget->setGtsTotalMgr(this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pAxisWidget);
    m_pIOWidget = new IOWidget(this);
    m_pIOWidget->setGtsTotalMgr(this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pIOWidget);
    m_pConfigWidget = new ConfigWidget(this);
    m_pConfigWidget->setGtsTotalMgr(this->m_pTotalMgr);
    ui.stackedWidget->addWidget(m_pConfigWidget);
    m_pOthersWidget = new OthersWidget(this);
    ui.stackedWidget->addWidget(m_pOthersWidget);
    // 默认显示板卡页面
    ui.stackedWidget->setCurrentIndex(0);
}

void GTSControllerWidget::InitUISignalAndSlotConnect()
{
    ui.toolButton_Board->setCheckable(true);
    ui.toolButton_masterControl->setCheckable(true);
    ui.toolButton_Axis->setCheckable(true);
    ui.toolButton_IO->setCheckable(true);
    ui.toolButton_Config->setCheckable(true);
    ui.toolButton_Others->setCheckable(true);
    m_pBtnGroup = new QButtonGroup(this);
    m_pBtnGroup->addButton(ui.toolButton_Board, 0);
    m_pBtnGroup->addButton(ui.toolButton_masterControl, 1);
    m_pBtnGroup->addButton(ui.toolButton_Axis, 2);
    m_pBtnGroup->addButton(ui.toolButton_IO, 3);
    m_pBtnGroup->addButton(ui.toolButton_Config, 4);
    m_pBtnGroup->addButton(ui.toolButton_Others, 5);

    ui.toolButton_Board->setChecked(true);
    connect(m_pBtnGroup, &QButtonGroup::idClicked, this, &GTSControllerWidget::OnBtnClicked);
}

void GTSControllerWidget::InitMgrSignalAndSlotConnect()
{
    connect(m_pTotalMgr, &GtsMgr::logMessage, this, &GTSControllerWidget::showLog);

    // 显示错误信息
    auto errorHandler = [this](short axis, short errorCode, const QString& errorMsg) {
        showLog(QStringLiteral("轴%1 错误 [%2] %3")
            .arg(axis)
            .arg(errorCode)
            .arg(errorMsg),
            Qt::red);
    };

    connect(m_pTotalMgr->axisMgr(), &AxisMgr::errorOccurred, this, errorHandler);
    connect(m_pTotalMgr->boardMgr(), &BoardMgr::errorOccurred, this, errorHandler);
    connect(m_pTotalMgr->motionMgr(), &MotionMgr::errorOccurred, this, errorHandler);
    connect(m_pTotalMgr->configMgr() , &ConfigMgr::errorOccurred, this, errorHandler);
    connect(m_pTotalMgr->feedbackMgr(), &FeedbackMgr::errorOccurred, this, errorHandler);
    connect(m_pTotalMgr->coordMgr(), &CoordMgr::errorOccurred, this, errorHandler);
}

void GTSControllerWidget::showLog(const QString& log, QColor color)
{
    if (m_bIsShuttingDown)
        return;

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
