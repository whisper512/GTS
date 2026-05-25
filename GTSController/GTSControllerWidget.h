#pragma once
#include <QtWidgets/QWidget>
#include <QButtonGroup>

#include "ui_GTSControllerWidget.h"
#include "BoardWidget.h"
#include "AxisWidget.h"
#include "InterpWidget.h"
#include "IOWidget.h"
#include "FeedbackWidget.h"
#include "ConfigWidget.h"
#include "OthersWidget.h"


class GTSControllerWidget : public QWidget
{
    Q_OBJECT

public:
    GTSControllerWidget(QWidget *parent = nullptr);
    ~GTSControllerWidget();

private:
    CBoardWidget* m_pBoardWidget = nullptr;  // 板卡
    QWidget* m_pAxisWidget = nullptr;        // 单轴
    QWidget* m_pInterpWidget = nullptr;      // 插补
    QWidget* m_pIOWidget = nullptr;          // IO
    QWidget* m_pFeedbackWidget = nullptr;    // 编码器
    QWidget* m_pConfigWidget = nullptr;      // 设置
    QWidget* m_pOthersWidget = nullptr;      // 其他
    QButtonGroup* m_pBtnGroup = nullptr;

private:
    void Init();
    void InitUI();
    void InitSignalAndSlotConnect();



private:
    Ui::GTSControllerWidgetClass ui;

private slots:
    void OnBtnClicked(int id);
};

