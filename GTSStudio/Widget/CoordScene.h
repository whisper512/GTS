#pragma once
#include <QGraphicsScene>
#include <QPainter>

#include "../../GtsCore/CoordData.h"

enum class Projection
{
    XY = 0,
    YZ = 1,
    ZX = 2
};

// ============================================================
// GridScene — 插补场景, 带网格背景 + 路径绘制
// ============================================================

class GridScene : public QGraphicsScene
{
public:
    using QGraphicsScene::QGraphicsScene;

    void drawPath(const CoordTable& table, int executingIndex = -1,
                  Projection proj = Projection::XY);

    Projection currentProjection() const { return m_projection; }

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void drawForeground(QPainter* painter, const QRectF& rect) override;

private:
    Projection m_projection = Projection::XY;
};
