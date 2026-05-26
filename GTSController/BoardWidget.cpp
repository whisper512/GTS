#include <QTimer>

#include "BoardWidget.h"
#include "TotalMgr.h"
#include "BoardMgr.h"

CBoardWidget::CBoardWidget(QWidget *parent, CTotalMgr* mgr)
	: QWidget(parent)
	, m_pTotalMgr(mgr)
{
	ui.setupUi(this);
    ConnectPrivateSignal();
}

CBoardWidget::~CBoardWidget()
{}

void CBoardWidget::ConnectPrivateSignal()
{
    QTimer::singleShot(0, this, [this](){
        connect(ui.pushButton_openBoard, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_closeBoard, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_resetBoard, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_getBoardID, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_setBoardID, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_loadCfgFile, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_saveCfgFile, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_UploadcfgFile, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_downloadCfgFile, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_getHardwareVer, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_getDevicerVer, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_getClock, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);
        connect(ui.pushButton_getHighPrecisionClock, &QPushButton::clicked, this, &CBoardWidget::OnBtnClick);

        });
}

void CBoardWidget::OnBtnClick()
{
    if (!m_pTotalMgr) return;

    // 获取发送信号的对象
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString objName = btn->objectName();
    if (objName == "pushButton_openBoard") {
        m_pTotalMgr->boardMgr()->open(0, 1);
    }
    if (objName == "pushButton_closeBoard") {
        m_pTotalMgr->boardMgr()->close();
    }
    if (objName == "pushButton_resetBoard") {
        m_pTotalMgr->boardMgr()->reset();
    }
    if (objName == "pushButton_getBoardID") {
        short id = m_pTotalMgr->boardMgr()->getCardNo();
    }
    if (objName == "pushButton_setBoardID") {
        m_pTotalMgr->boardMgr()->setCardNo(0);
    }
    if (objName == "pushButton_loadCfgFile") {
        m_pTotalMgr->boardMgr()->loadConfig("");
    }
    if (objName == "pushButton_saveCfgFile") {

    }
    if (objName == "pushButton_UploadcfgFile") {

    }
    if (objName == "pushButton_downloadCfgFile") {

    }
    if (objName == "pushButton_getHardwareVer") {
        m_pTotalMgr->boardMgr()->firmwareVersion();
    }
    if (objName == "pushButton_getDevicerVer") {
        m_pTotalMgr->boardMgr()->driverVersion();
    }
    if (objName == "pushButton_getClock") {
        m_pTotalMgr->boardMgr()->clock();
    }
    if (objName == "pushButton_getHighPrecisionClock") {
        m_pTotalMgr->boardMgr()->clockHighPrecision();
    }

    
}


