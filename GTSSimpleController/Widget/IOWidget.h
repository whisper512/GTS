#pragma once
#include <QWidget>
#include <QMap>

#include "ControllerData.h"
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
	// 本地缓存的 DO 状态
	stuDO m_doState;

private:
	void InitUI();
	void InitTableDI();
    void InitTableDO();
	void InitTableCommon(QTableWidget* table, int totalRows, const Block* blocks, int blockCount);
	void connectPrivateSignal();    
	void RefreshTable(QTableWidget* table, const std::vector<int>& status);
	void onDOCellClicked(int row, int col);
	// 双击处理
	void onDICellDoubleClicked(int row, int col);
	void onDOCellDoubleClicked(int row, int col);
	void onDescriptionEdited(int row, bool isDI);
public slots:
	void onDIUpdated(const stuDI& di);     
	void onDOUpdated(const stuDO& dout);  

};

