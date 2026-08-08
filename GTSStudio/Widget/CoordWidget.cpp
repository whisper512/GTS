#include <QHeaderView>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QStyledItemDelegate>

#include "CoordWidget.h"
#include "../../GtsCore/GtsMgr.h"

// 插补类型comboBox代理
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

// 圆弧方向comboBox代理
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

// 数值编辑器代理
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

    connect(ui.btnAdd, &QPushButton::clicked, this, &CoordWidget::addRowToTable);
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

    connect(tw, &QTableWidget::cellChanged, this, &CoordWidget::onCellChanged);
}

void CoordWidget::addRowToTable()
{
    auto* tw = ui.tableWidget;
    int row = tw->rowCount();
    tw->insertRow(row);

    // 段号
    auto* noItem = new QTableWidgetItem(QString::number(row + 1));
    noItem->setFlags(noItem->flags() & ~Qt::ItemIsEditable);
    noItem->setTextAlignment(Qt::AlignCenter);
    tw->setItem(row, 0, noItem);

    // 默认值: 直线, (0,0), F=200, R=0, CW
    tw->setItem(row, 1, new QTableWidgetItem(QStringLiteral("直线")));
    tw->setItem(row, 2, new QTableWidgetItem(QStringLiteral("0")));
    tw->setItem(row, 3, new QTableWidgetItem(QStringLiteral("0")));
    tw->setItem(row, 4, new QTableWidgetItem(QStringLiteral("200")));
    tw->setItem(row, 5, new QTableWidgetItem(QStringLiteral("0")));
    tw->setItem(row, 6, new QTableWidgetItem(QStringLiteral("CW")));

    // 选中新行，打开编辑
    tw->selectRow(row);
    updateRowState(row);
    syncTableToScene();
    tw->edit(tw->model()->index(row, 1));
}

void CoordWidget::onCellChanged(int row, int col)
{
    if (col == 1) updateRowState(row);
    syncTableToScene();
}

void CoordWidget::updateRowState(int row)
{
    auto* tw = ui.tableWidget;
    auto* typeItem = tw->item(row, 1);
    bool isArc = typeItem && typeItem->text() == QStringLiteral("圆弧");

    for (int col : {5, 6}) {
        auto* item = tw->item(row, col);
        if (!item) continue;

        if (isArc) {
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            item->setBackground(Qt::white);
        }
        else {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            item->setBackground(QColor(220, 220, 220));
        }
    }
}

void CoordWidget::syncTableToScene()
{
    auto* tw = ui.tableWidget;
    int n = tw->rowCount();
    CoordTable table;

    for (int i = 0; i < n; ++i) {
        CoordSegment seg;
        auto* typeItem = tw->item(i, 1);
        seg.type = (typeItem && typeItem->text() == QStringLiteral("圆弧"))
            ? SegmentType::Arc : SegmentType::Line;
        seg.x = tw->item(i, 2) ? tw->item(i, 2)->text().toDouble() : 0;
        seg.y = tw->item(i, 3) ? tw->item(i, 3)->text().toDouble() : 0;
        seg.f = tw->item(i, 4) ? tw->item(i, 4)->text().toDouble() : 200;
        seg.r = tw->item(i, 5) ? tw->item(i, 5)->text().toDouble() : 0;
        auto* dirItem = tw->item(i, 6);
        seg.dir = (dirItem && dirItem->text() == QStringLiteral("CCW")) ? ArcDir::CCW : ArcDir::CW;
        table.push_back(seg);
    }

    m_scene->drawPath(table, m_executingIndex);
    ui.graphicsView->fitInView(m_scene->sceneRect().adjusted(-20, -20, 20, 20), Qt::KeepAspectRatio);
}
