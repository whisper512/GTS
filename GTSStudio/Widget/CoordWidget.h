#pragma once

#include <QWidget>
#include <QGraphicsScene>
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
	QGraphicsScene* m_scene = nullptr;

private slots:
};
