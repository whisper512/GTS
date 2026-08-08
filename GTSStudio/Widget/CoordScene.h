#pragma once

#include <QGraphicsScene>
#include <QPainter>
#include "../../GtsCore/CoordData.h"

// ============================================================
// GridScene — 插补场景, 带网格背景 + 路径绘制
// ============================================================

class GridScene : public QGraphicsScene
{
public:
    using QGraphicsScene::QGraphicsScene;

    void drawPath(const CoordTable& table, int executingIndex = -1);

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
};
