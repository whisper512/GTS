#include "CoordWidget.h"
#include "../../GtsCore/GtsMgr.h"
#include <QPainter>
#include <cmath>

// ---- 带网格背景的 Scene ----
class GridScene : public QGraphicsScene
{
public:
    using QGraphicsScene::QGraphicsScene;
protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override
    {
        // 浅黑背景
        painter->fillRect(rect, QColor(35, 35, 38));

        const double gridSize = 100.0;
        double left  = std::floor(rect.left()   / gridSize) * gridSize;
        double top   = std::floor(rect.top()    / gridSize) * gridSize;
        double right = rect.right();
        double bottom = rect.bottom();

        QPen pen(QColor(55, 55, 60), 1);
        painter->setPen(pen);

        for (double x = left; x < right; x += gridSize)
            painter->drawLine(QPointF(x, top), QPointF(x, bottom));
        for (double y = top; y < bottom; y += gridSize)
            painter->drawLine(QPointF(left, y), QPointF(right, y));
    }
};

CoordWidget::CoordWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_scene = new GridScene(this);
    ui.graphicsView->setScene(m_scene);
    ui.graphicsView->scale(1, -1); // Y 轴向上
}

CoordWidget::~CoordWidget()
{
    m_gtsMgr = nullptr;
}

void CoordWidget::setGtsTotalMgr(GtsMgr* mgr)
{
    m_gtsMgr = mgr;
}
