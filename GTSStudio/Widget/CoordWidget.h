#pragma once
#include <QWidget>

#include "CoordScene.h"
#include "ui_CoordWidget.h"

class GtsMgr;

class CoordWidget : public QWidget
{
	Q_OBJECT

public:
	CoordWidget(QWidget* parent = nullptr);
	~CoordWidget();
	void setGtsTotalMgr(GtsMgr* mgr);

private:
	Ui::CCoordWidgetClass ui;
	GtsMgr* m_gtsMgr = nullptr;
	// 绘图场景
	GridScene* m_scene = nullptr;
	// 当前行索引
	int m_executingIndex = -1;

	void initTable();
	void addRowToTable();
	void deleteRow();
	void clearAll();

	// 更新表格行状态
	void updateRowState(int row);
	// 同步表格数据到场景
	void syncTableToScene();
	// 验证圆弧半径
	void validateArcR(int row);

private slots:
	void onCellChanged(int row, int col);
};
