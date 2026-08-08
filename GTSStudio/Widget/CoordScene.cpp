#define _USE_MATH_DEFINES
#include <cmath>
#include <QPen>
#include <QPainterPath>

#include "CoordScene.h"

void GridScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    // 浅黑背景
    painter->fillRect(rect, QColor(35, 35, 38));

    const double gridSize = 100.0;
    double left   = std::floor(rect.left()   / gridSize) * gridSize;
    double top    = std::floor(rect.top()    / gridSize) * gridSize;
    double right  = rect.right();
    double bottom = rect.bottom();

    QPen pen(QColor(55, 55, 60), 1);
    painter->setPen(pen);

    for (double x = left; x < right; x += gridSize)
        painter->drawLine(QPointF(x, top), QPointF(x, bottom));
    for (double y = top; y < bottom; y += gridSize)
        painter->drawLine(QPointF(left, y), QPointF(right, y));
}

void GridScene::drawPath(const CoordTable& table, int executingIndex)
{
    // 清除前景图形，保留背景网格
    auto items = this->items();
    for (auto* item : items)
        removeItem(item);

    if (table.empty()) return;

    double cx = 0, cy = 0;
    const double scale = 1.0;

    for (int i = 0; i < (int)table.size(); ++i) {
        const auto& seg = table[i];
        double sx = cx, sy = cy;
        double ex = seg.x, ey = seg.y;

        QColor color = Qt::cyan;
        if (executingIndex >= 0) {
            if (i < executingIndex)       color = Qt::green;
            else if (i == executingIndex) color = Qt::red;
        }

        QPen pen(color, 2);

        if (seg.type != SegmentType::Arc || std::fabs(seg.r) < 0.01) {
            addLine(sx * scale, sy * scale, ex * scale, ey * scale, pen);
        }
        else {
            double dx = ex - sx, dy = ey - sy;
            double chord = std::sqrt(dx * dx + dy * dy);
            double r = std::fabs(seg.r);
            if (chord > 2.0 * r) chord = 2.0 * r;

            double mx = (sx + ex) / 2.0, my = (sy + ey) / 2.0;
            double halfChord = chord / 2.0;
            double d = std::sqrt(std::max(0.0, r * r - halfChord * halfChord));
            double nx = -dy, ny = dx;
            double nlen = std::sqrt(nx * nx + ny * ny);
            if (nlen > 0) { nx /= nlen; ny /= nlen; }

            double cxArc = mx + (seg.dir == ArcDir::CCW ? -nx : nx) * d;
            double cyArc = my + (seg.dir == ArcDir::CCW ? -ny : ny) * d;

            double sa = std::atan2(sy - cyArc, sx - cxArc) * 180.0 / M_PI;
            double ea = std::atan2(ey - cyArc, ex - cxArc) * 180.0 / M_PI;
            double sweep = ea - sa;

            if (seg.dir == ArcDir::CCW && sweep < 0) sweep += 360.0;
            if (seg.dir == ArcDir::CW  && sweep > 0) sweep -= 360.0;

            QRectF arcR((cxArc - r) * scale, (cyArc - r) * scale, 2 * r * scale, 2 * r * scale);
            QPainterPath path;
            path.arcMoveTo(arcR, sa);
            path.arcTo(arcR, sa, sweep);
            addPath(path, pen);
        }

        // 节点圆点
        addEllipse(ex * scale - 4, ey * scale - 4, 8, 8, QPen(color), QBrush(color));
        // 起点标记
        if (i == 0)
            addEllipse(sx * scale - 5, sy * scale - 5, 10, 10, QPen(Qt::white), QBrush(Qt::white));

        cx = ex; cy = ey;
    }
}
