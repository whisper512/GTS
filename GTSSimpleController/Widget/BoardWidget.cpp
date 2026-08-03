#include <QTimer>
#include <QPushButton>
#include "BoardWidget.h"
#include "../../GtsCore/GtsMgr.h"

CBoardWidget::CBoardWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    initConnections();
    updateBoardState(false);
}

CBoardWidget::~CBoardWidget()
{
    m_gtsMgr = nullptr;
}

void CBoardWidget::setGtsTotalMgr(GtsMgr* mgr)
{
    if (m_gtsMgr)
    {
        disconnect(m_gtsMgr, &GtsMgr::boardClockUpdated, this, &CBoardWidget::onBoardClockUpdated);
    }
    m_gtsMgr = mgr;
    if (m_gtsMgr)
    {
        connect(m_gtsMgr, &GtsMgr::boardClockUpdated, this, &CBoardWidget::onBoardClockUpdated);
    }
}

void CBoardWidget::initConnections()
{
    ui.radioButton_boardState->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QTimer::singleShot(0, this, [this]() {
        connect(ui.pushButton_openBoard, &QPushButton::clicked, this, &CBoardWidget::onBtnClick);
        connect(ui.pushButton_closeBoard, &QPushButton::clicked, this, &CBoardWidget::onBtnClick);
        connect(ui.pushButton_resetBoard, &QPushButton::clicked, this, &CBoardWidget::onBtnClick);
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

void CBoardWidget::onOpen()
{
    if (!m_gtsMgr) return;
    bool ok = m_gtsMgr->boardMgr()->open(0, 1);
    if (ok) {
        updateBoardState(true);
        short id = m_gtsMgr->boardMgr()->getCardNo();
        ui.label_boardIDData->setText(QString::number(id));
        QString fwVersion = m_gtsMgr->boardMgr()->firmwareVersion();
        ui.label_hardwareVerData->setText(fwVersion);
    }
}

void CBoardWidget::onClose()
{
    if (!m_gtsMgr) return;
    bool ok = m_gtsMgr->boardMgr()->close();
    if (ok) updateBoardState(false);
}

void CBoardWidget::onReset()
{
    if (!m_gtsMgr) return;
    bool ok = m_gtsMgr->boardMgr()->reset();
    if (ok) updateBoardState(false);
}

void CBoardWidget::onBoardClockUpdated(const Clock& clock)
{
    ui.label_clockData->setText(QString::number(clock.sysClock));
    ui.label_highPrecisionClockData->setText(QString::number(clock.highPrecClock));
}

void CBoardWidget::onBtnClick()
{
    if (!m_gtsMgr) return;
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString objName = btn->objectName();
    if (objName == "pushButton_openBoard") {
        onOpen();
    }
    else if (objName == "pushButton_closeBoard") {
        onClose();
    }
    else if (objName == "pushButton_resetBoard") {
        onReset();
    }
}
