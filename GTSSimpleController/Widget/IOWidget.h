#pragma once
#include <QWidget>
#include <QMap>

#include "../../GtsCore/ControllerData.h"
#include "ui_IOWidget.h"

class GtsMgr;

struct Block { int start; int count; QString desc; };

class CIOWidget : public QWidget
{
	Q_OBJECT

public:
	CIOWidget(QWidget* parent = nullptr);
	~CIOWidget();
	void setGtsTotalMgr(GtsMgr* mgr);

private:
	Ui::CIOWidgetClass ui;
	GtsMgr* m_gtsMgr = nullptr;
	DO m_doState;

	void InitUI();
	void InitTableDI();
	void InitTableDO();
	void InitTableCommon(QTableWidget* table, int totalRows, const Block* blocks, int blockCount);
	void connectPrivateSignal();
	void RefreshTable(QTableWidget* table, const std::vector<int>& status);
	void onDOCellClicked(int row, int col);
	void onDICellDoubleClicked(int row, int col);
	void onDOCellDoubleClicked(int row, int col);
	void onDescriptionEdited(int row, bool isDI);

public slots:
	void onDIUpdated(const DI& di);
	void onDOUpdated(const DO& dout);
	void onConfigReloaded();
};
