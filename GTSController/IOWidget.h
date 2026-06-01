#pragma once
#include <QWidget>
#include "ui_IOWidget.h"

class CTotalMgr;
class GTSControllerWidget;

struct Block { int start; int count; QString desc; };

class CIOWidget : public QWidget
{
	Q_OBJECT

public:
	CIOWidget(QWidget* parent = nullptr, CTotalMgr* mgr = nullptr);
	~CIOWidget();

private:
	Ui::CIOWidgetClass ui;
	CTotalMgr* m_pTotalMgr = nullptr;
	GTSControllerWidget* m_pGTSControllerWidget = nullptr;


private:
	void InitUI();
	void InitTableDI();
    void InitTableDO();
	void InitTableCommon(QTableWidget* table, int totalRows, const Block* blocks, int blockCount);
	void connectPrivateSignal();
};

