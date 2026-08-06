#include "CoordWidget.h"
#include "../../GtsCore/GtsMgr.h"
#include <QPainter>
#include <QHeaderView>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QStyledItemDelegate>
#include <cmath>

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

class TypeDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const override
    {
        auto* cb = new QComboBox(parent);
        cb->addItem(QStringLiteral("直线"));
        cb->addItem(QStringLiteral("圆弧"));
        return cb;
    }
    void setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        auto* cb = qobject_cast<QComboBox*>(editor);
        if (cb) cb->setCurrentText(index.data(Qt::EditRole).toString());
    }
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
        auto* cb = qobject_cast<QComboBox*>(editor);
        if (cb) model->setData(index, cb->currentText());
    }
};

class DirDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const override
    {
        auto* cb = new QComboBox(parent);
        cb->addItem(QStringLiteral("CW"));
        cb->addItem(QStringLiteral("CCW"));
        return cb;
    }
    void setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        auto* cb = qobject_cast<QComboBox*>(editor);
        if (cb) cb->setCurrentText(index.data(Qt::EditRole).toString());
    }
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
        auto* cb = qobject_cast<QComboBox*>(editor);
        if (cb) model->setData(index, cb->currentText());
    }
};

class DoubleDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const override
    {
        auto* sb = new QDoubleSpinBox(parent);
        sb->setRange(-99999.99, 99999.99);
        sb->setDecimals(2);
        sb->setSingleStep(10.0);
        return sb;
    }
    void setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        auto* sb = qobject_cast<QDoubleSpinBox*>(editor);
        if (sb) sb->setValue(index.data(Qt::EditRole).toDouble());
    }
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
        auto* sb = qobject_cast<QDoubleSpinBox*>(editor);
        if (sb) model->setData(index, sb->value());
    }
};

CoordWidget::CoordWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_scene = new GridScene(this);
    ui.graphicsView->setScene(m_scene);
    ui.graphicsView->scale(1, -1); // Y 轴向上

    initTable();
}

CoordWidget::~CoordWidget()
{
    m_gtsMgr = nullptr;
}

void CoordWidget::setGtsTotalMgr(GtsMgr* mgr)
{
    m_gtsMgr = mgr;
}

void CoordWidget::initTable()
{
    auto* tw = ui.tableWidget;
    tw->setColumnCount(7);
    tw->setHorizontalHeaderLabels({
        QStringLiteral("段号"),
        QStringLiteral("类型"),
        QStringLiteral("X (mm)"),
        QStringLiteral("Y (mm)"),
        QStringLiteral("F (mm/s)"),
        QStringLiteral("R (mm)"),
        QStringLiteral("方向")
    });
    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tw->verticalHeader()->setVisible(false);
    tw->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    tw->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 段号列只读
    tw->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);

    // 注册代理
    tw->setItemDelegateForColumn(1, new TypeDelegate(tw));
    tw->setItemDelegateForColumn(2, new DoubleDelegate(tw));
    tw->setItemDelegateForColumn(3, new DoubleDelegate(tw));
    tw->setItemDelegateForColumn(4, new DoubleDelegate(tw));
    tw->setItemDelegateForColumn(5, new DoubleDelegate(tw));
    tw->setItemDelegateForColumn(6, new DirDelegate(tw));

    auto addRow = [&](int seq, const QString& type, double x, double y, double f, double r, const QString& dir) {
        int row = tw->rowCount();
        tw->insertRow(row);
        auto* noItem = new QTableWidgetItem(QString::number(seq));
        noItem->setFlags(noItem->flags() & ~Qt::ItemIsEditable);
        noItem->setTextAlignment(Qt::AlignCenter);
        tw->setItem(row, 0, noItem);
        tw->setItem(row, 1, new QTableWidgetItem(type));
        tw->setItem(row, 2, new QTableWidgetItem(QString::number(x, 'f', 2)));
        tw->setItem(row, 3, new QTableWidgetItem(QString::number(y, 'f', 2)));
        tw->setItem(row, 4, new QTableWidgetItem(QString::number(f, 'f', 2)));
        tw->setItem(row, 5, new QTableWidgetItem(QString::number(r, 'f', 2)));
        tw->setItem(row, 6, new QTableWidgetItem(dir));
    };

}
