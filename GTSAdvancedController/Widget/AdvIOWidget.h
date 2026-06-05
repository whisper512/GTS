#pragma once
#include <QWidget>

#include "../Mgr/AdvControllerData.h"
#include "ui_AdvIOWidget.h"

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
	// ±¾µØ»º´æµÄ DO ×´Ì¬
	stuDO m_doState;


private:
	void InitUI();
	void InitTableDI();
    void InitTableDO();
	void InitTableCommon(QTableWidget* table, int totalRows, const Block* blocks, int blockCount);
	void connectPrivateSignal();
	void RefreshTable(QTableWidget* table, const std::vector<int>& status);
	void onDOCellClicked(int row, int col);
public slots:
	void onDIUpdated(const stuDI& di);     
	void onDOUpdated(const stuDO& dout);  

};

