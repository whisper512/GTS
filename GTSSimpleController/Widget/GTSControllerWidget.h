#pragma once
#include <QtWidgets/QWidget>
#include <QButtonGroup>

#include "ui_GTSControllerWidget.h"

#include "../../GtsCore/GtsMgr.h"
#include "BoardWidget.h"
#include "MasterControlWidget.h"
#include "AxisWidget.h"
#include "IOWidget.h"
#include "ConfigWidget.h"
#include "OthersWidget.h"


class GTSControllerWidget : public QWidget
{
    Q_OBJECT

public:
    GTSControllerWidget(QWidget *parent = nullptr);
    ~GTSControllerWidget();

private:
    GtsMgr* m_pTotalMgr = nullptr;                          // 总管理
    BoardWidget* m_pBoardWidget = nullptr;                 // 板卡
    MasterControlWidget* m_pMasterControlWidget = nullptr; // 主控
    AxisWidget* m_pAxisWidget = nullptr;                   // 单轴
    IOWidget* m_pIOWidget = nullptr;                       // IO
    ConfigWidget* m_pConfigWidget = nullptr;               // 设置
    QWidget* m_pOthersWidget = nullptr;                     // 其他
    QButtonGroup* m_pBtnGroup = nullptr;

    bool m_bIsShuttingDown = false;
private:
    void Init();
    void InitUI();
    void InitUISignalAndSlotConnect();
    void InitMgrSignalAndSlotConnect();


private:
    Ui::GTSControllerWidgetClass ui;

public slots:
    void showLog(const QString& log = "", QColor color = Qt::black);

private slots:
    void OnBtnClicked(int id);
};

