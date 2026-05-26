#include <QTimer>

#include "GTSControllerWidget.h"
#include "BoardWidget.h"
#include "TotalMgr.h"
#include "BoardMgr.h"

CBoardWidget::CBoardWidget(QWidget* parent, CTotalMgr* mgr)
    : QWidget(parent)
    , m_pTotalMgr(mgr)
{
    ui.setupUi(this);
    m_pGTSControllerWidget = qobject_cast<GTSControllerWidget*>(parent);

    // 创建定时器
    m_pClockTimer = new QTimer(this);
    connect(m_pClockTimer, &QTimer::timeout, this, &CBoardWidget::OnUpdateClock);

    ConnectPrivateSignal();
}

CBoardWidget::~CBoardWidget()
{
    if (m_pClockTimer) {
        m_pClockTimer->stop();
    }
}

void CBoardWidget::ConnectPrivateSignal()
{
    ui.radioButton_boardState->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QTimer::singleShot(0, this, [this]() {
        connect(ui.pushButton_openBoard, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_closeBoard, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_resetBoard, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        });
}

void CBoardWidget::updateBoardState(bool isOpen)
{
    ui.radioButton_boardState->setChecked(isOpen);
    if (isOpen) {
        ui.radioButton_boardState->setText(QStringLiteral("已打开"));
        ui.radioButton_boardState->setStyleSheet(
            "QRadioButton { color: green; font-weight: bold; }");
    }
    else {
        ui.radioButton_boardState->setText(QStringLiteral("已关闭"));
        ui.radioButton_boardState->setStyleSheet(
            "QRadioButton { color: red; }");
    }
}

void CBoardWidget::OnOpen()
{
    bool ok = m_pTotalMgr->boardMgr()->open(0, 1);
    if (ok) {
        updateBoardState(true);
        m_pGTSControllerWidget->showLog(QStringLiteral("打开板卡成功"), Qt::darkGreen);
    }
    else {
        m_pGTSControllerWidget->showLog(QStringLiteral("打开板卡失败"), Qt::red);
        return;
    }

    // 获取并显示板卡编号
    short id = m_pTotalMgr->boardMgr()->getCardNo();
    ui.label_boardIDData->setText(QString::number(id));
    m_pGTSControllerWidget->showLog(QStringLiteral("板卡编号: %1").arg(id), Qt::darkGreen);

    // 获取并显示固件版本
    QString fwVersion = m_pTotalMgr->boardMgr()->firmwareVersion();
    ui.label_hardwareVerData->setText(fwVersion);
    m_pGTSControllerWidget->showLog(QStringLiteral("固件版本: %1").arg(fwVersion), Qt::darkGreen);

    
    OnUpdateClock();
    m_pClockTimer->start(1000);
}

void CBoardWidget::OnClose()
{
    bool ok = m_pTotalMgr->boardMgr()->close();
    if (ok) {
        updateBoardState(false);
        m_pClockTimer->stop();
        m_pGTSControllerWidget->showLog(QStringLiteral("关闭板卡成功"), Qt::darkGreen);
    }
    else {
        m_pGTSControllerWidget->showLog(QStringLiteral("关闭板卡失败"), Qt::red);
    }
}

void CBoardWidget::OnReset()
{
    bool ok = m_pTotalMgr->boardMgr()->reset();
    if (ok) {
        updateBoardState(false);
        m_pClockTimer->stop();
        m_pGTSControllerWidget->showLog(QStringLiteral("复位板卡成功"), Qt::darkGreen);
    }
    else {
        m_pGTSControllerWidget->showLog(QStringLiteral("复位板卡失败"), Qt::red);
    }
}


void CBoardWidget::OnUpdateClock()
{
    if (!m_pTotalMgr->boardMgr()->isOpen()) return;

    // 系统时钟
    unsigned long sysClock = m_pTotalMgr->boardMgr()->clock();
    ui.label_clockData->setText(QString::number(sysClock));

    // 高精度时钟
    unsigned long highPrecClock = m_pTotalMgr->boardMgr()->clockHighPrecision();
    ui.label_highPrecisionClockData->setText(QString::number(highPrecClock));
}

void CBoardWidget::OnBtnClick()
{
    if (!m_pTotalMgr) return;
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString objName = btn->objectName();
    if (objName == "pushButton_openBoard") {
        OnOpen();
    }
    else if (objName == "pushButton_closeBoard") {
        OnClose();
    }
    else if (objName == "pushButton_resetBoard") {
        OnReset();
    }
}
