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

void GridScene::drawPath(const CoordTable& table, int executingIndex, Projection proj)
{
    m_projection = proj;
    m_hasData = !table.empty();

    // 清除前景图形，保留背景网格
    auto items = this->items();
    for (auto* item : items)
        removeItem(item);

    if (table.empty()) return;

    // 根据投影提取 XY
    auto getX = [proj](const CoordSegment& s) -> double {
        switch (proj) {
        case Projection::XY: return s.x;
        case Projection::YZ: return s.y;
        case Projection::ZX: return s.x;
        } return s.x;
    };
    auto getY = [proj](const CoordSegment& s) -> double {
        switch (proj) {
        case Projection::XY: return s.y;
        case Projection::YZ: return s.z;
        case Projection::ZX: return s.z;
        } return s.y;
    };

    double cx = 0, cy = 0;
    const double scale = 1.0;

    for (int i = 0; i < (int)table.size(); ++i) {
        const auto& seg = table[i];
        double sx = cx, sy = cy;
        double ex = getX(seg), ey = getY(seg);

        QColor color = Qt::cyan;
        if (executingIndex >= 0 && i <= executingIndex) {
            color = Qt::red; // 已执行(含当前段)保持红色
        }

        QPen pen(color, 2);

        if (seg.type != SegmentType::Arc || std::fabs(seg.r) < 0.01 ||
            static_cast<Projection>(seg.plane) != proj) {
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

void GridScene::drawForeground(QPainter* painter, const QRectF& rect)
{
    if (!m_hasData) return;
    const double len = 30.0;
    double ox = rect.left() + 40.0;
    double oy = rect.bottom() - 40.0;

    // 切换到设备坐标, 避免 scale(1,-1) 导致文字倒置
    painter->save();
    QPointF dp = painter->combinedTransform().map(QPointF(ox, oy));
    painter->resetTransform();

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    QString hLabel, vLabel;
    switch (m_projection) {
    case Projection::XY: hLabel = "X"; vLabel = "Y"; break;
    case Projection::YZ: hLabel = "Y"; vLabel = "Z"; break;
    case Projection::ZX: hLabel = "X"; vLabel = "Z"; break;
    }

    // 横轴 - 红色 (右)
    painter->setPen(QPen(Qt::red, 3));
    painter->drawLine(QPointF(dp.x(), dp.y()), QPointF(dp.x() + len, dp.y()));
    painter->drawText(QPointF(dp.x() + len + 4, dp.y() + 12), hLabel);

    // 纵轴 - 绿色 (上, 设备坐标中 y 减小)
    painter->setPen(QPen(Qt::green, 3));
    painter->drawLine(QPointF(dp.x(), dp.y()), QPointF(dp.x(), dp.y() - len));
    painter->drawText(QPointF(dp.x() - 14, dp.y() - len - 2), vLabel);

    painter->restore();
}
