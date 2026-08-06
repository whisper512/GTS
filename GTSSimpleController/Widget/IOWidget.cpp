#include <QTimer>
#include <QStyledItemDelegate>
#include <QInputDialog>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>

#include "IOWidget.h"
#include "../../GtsCore/GtsMgr.h"


// 状态列专用代理:忽略选中态，让 setBackground() 的背景始终可见
class StatusDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override
    {
        QStyledItemDelegate::initStyleOption(option, index);
        option->state &= ~QStyle::State_Selected;
    }
};

IOWidget::IOWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    InitUI();
    connectPrivateSignal();
}

IOWidget::~IOWidget()
{
    m_gtsMgr = nullptr;
}

void IOWidget::setGtsTotalMgr(GtsMgr* mgr)
{
    if (m_gtsMgr) {
        disconnect(m_gtsMgr, &GtsMgr::diUpdated, this, &IOWidget::onDIUpdated);
        disconnect(m_gtsMgr, &GtsMgr::doUpdated, this, &IOWidget::onDOUpdated);
    }
    m_gtsMgr = mgr;
    if (m_gtsMgr) {
        connect(m_gtsMgr, &GtsMgr::diUpdated, this, &IOWidget::onDIUpdated);
        connect(m_gtsMgr, &GtsMgr::doUpdated, this, &IOWidget::onDOUpdated);
    }
}

void IOWidget::InitUI()
{
    QTimer::singleShot(0, this, [this]() {
        InitTableDI();
        InitTableDO();
    });
}

void IOWidget::InitTableDI()
{
    const Block blocks[] = {
        {  0,  8, QStringLiteral("正限位信号0xF")    },
        {  8,  8, QStringLiteral("负限位信号0xF")    },
        { 16,  8, QStringLiteral("驱动报警0xF")      },
        { 24,  8, QStringLiteral("原点信号0xF")      },
        { 32, 16, QStringLiteral("通用输入0xFFFF")   },
        { 48,  8, QStringLiteral("电机到位0xF")      },
        { 56,  7, QStringLiteral("手轮输入0x7F")     },
    };

    InitTableCommon(ui.tableWidget_DI, 64, blocks, sizeof(blocks) / sizeof(blocks[0]));

    // 覆盖自定义描述
    const auto& diDesc = m_gtsMgr->configMgr()->customDIDescriptions();
    for (auto it = diDesc.begin(); it != diDesc.end(); ++it) {
        QTableWidgetItem* item = ui.tableWidget_DI->item(it.key(), 0);
        if (item) item->setText(it.value());
    }
}

void IOWidget::InitTableDO()
{
    const Block blocks[] = {
        {  0,  8, QStringLiteral("伺服使能0xF")      },
        {  8,  8, QStringLiteral("报警清除0xFF")     },
        { 16, 16, QStringLiteral("通用输出0xFFFF")   },
    };

    InitTableCommon(ui.tableWidget_DO, 32, blocks, sizeof(blocks) / sizeof(blocks[0]));

    // 覆盖自定义描述
    const auto& doDesc = m_gtsMgr->configMgr()->customDODescriptions();
    for (auto it = doDesc.begin(); it != doDesc.end(); ++it) {
        QTableWidgetItem* item = ui.tableWidget_DO->item(it.key(), 0);
        if (item) item->setText(it.value());
    }
}

void IOWidget::InitTableCommon(QTableWidget* table, int totalRows,
    const Block* blocks, int blockCount)
{
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({
        QStringLiteral("功能描述"),
        QStringLiteral("序号"),
        QStringLiteral("状态")
        });
    table->verticalHeader()->setVisible(false);
    table->setRowCount(totalRows);

    for (int b = 0; b < blockCount; ++b) {
        int No = 1;
        for (int i = blocks[b].start; i < blocks[b].start + blocks[b].count; ++i) {
            // 功能描述
            table->setItem(i, 0, new QTableWidgetItem(blocks[b].desc));

            // 序号
            auto* idxItem = new QTableWidgetItem(QString::number(No++));
            idxItem->setTextAlignment(Qt::AlignCenter);
            table->setItem(i, 1, idxItem);

            // 状态（默认关）
            auto* stsItem = new QTableWidgetItem(QStringLiteral("● 关"));
            stsItem->setTextAlignment(Qt::AlignCenter);
            table->setItem(i, 2, stsItem);
        }
    }

    // 样式
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->setColumnWidth(1, 60);
    table->setColumnWidth(2, 90);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setStyleSheet(
        QStringLiteral(
            "QTableWidget::item:selected { background: rgba(0,160,0,40); color: inherit; }"
        ));
    table->setItemDelegateForColumn(2, new StatusDelegate(table));
}


void IOWidget::connectPrivateSignal()
{
    connect(ui.tableWidget_DO, &QTableWidget::cellClicked, this, &IOWidget::onDOCellClicked);

    connect(ui.tableWidget_DI, &QTableWidget::cellDoubleClicked,
        this, &IOWidget::onDICellDoubleClicked);
    connect(ui.tableWidget_DO, &QTableWidget::cellDoubleClicked,
        this, &IOWidget::onDOCellDoubleClicked);
}

void IOWidget::RefreshTable(QTableWidget* table, const std::vector<int>& status)
{
    for (int i = 0; i < (int)status.size(); ++i) {
        QTableWidgetItem* item = table->item(i, 2);
        if (!item) continue;
        if (status[i]) {
            item->setText(QStringLiteral("● 开"));
            item->setBackground(Qt::green);
        }
        else {
            item->setText(QStringLiteral("● 关"));
            item->setBackground(Qt::white);
        }
    }
}

void IOWidget::onDOCellClicked(int row, int col)
{
    if (col != 2) return;
    if (!m_gtsMgr) return;
    IOMgr* ioMgr = m_gtsMgr->ioMgr();
    if (!ioMgr) return;
    // 取反对应位
    if (row >= 0 && row < 8) {
        // 伺服使能 (0~7)
        m_doState.servoOn[row] ^= 1;
        auto hwVec = m_doState.servoOn;
        for (int i = 0; i < (int)hwVec.size(); ++i) {
            if (m_gtsMgr->configMgr()->doInvertMap().value(i))
                hwVec[i] ^= 1;
        }
        ioMgr->setMotorEnableDO(hwVec);
    }
    else if (row >= 8 && row < 16) {
        // 报警清除 (8~15)
        int idx = row - 8;
        m_doState.almClear[idx] ^= 1;
        auto hwVec = m_doState.almClear;
        for (int i = 0; i < (int)hwVec.size(); ++i) {
            if (m_gtsMgr->configMgr()->doInvertMap().value(8 + i))
                hwVec[i] ^= 1;
        }
        ioMgr->setClearAlarmDO(hwVec);
    }
    else if (row >= 16 && row < 32) {
        // 通用输出 (16~31)
        int idx = row - 16;
        m_doState.GPO[idx] ^= 1;
        auto hwVec = m_doState.GPO;
        for (int i = 0; i < (int)hwVec.size(); ++i) {
            if (m_gtsMgr->configMgr()->doInvertMap().value(16 + i))
                hwVec[i] ^= 1;
        }
        ioMgr->setGPO(hwVec);
    }
    // 刷新该行显示
    auto flat = m_doState.toFlatVector();
    QTableWidgetItem* item = ui.tableWidget_DO->item(row, 2);
    if (item) {
        if (flat[row]) {
            item->setText(QStringLiteral("● 开"));
            item->setBackground(Qt::green);
        }
        else {
            item->setText(QStringLiteral("● 关"));
            item->setBackground(Qt::white);
        }
    }
}

void IOWidget::onDIUpdated(const DI& di)
{
    RefreshTable(ui.tableWidget_DI, di.toFlatVector());
}

void IOWidget::onDOUpdated(const DO& dout)
{
    m_doState = dout;
    RefreshTable(ui.tableWidget_DO, dout.toFlatVector());
}

void IOWidget::onDICellDoubleClicked(int row, int col)
{
    if (col == 0)
        onDescriptionEdited(row, true);
}

void IOWidget::onDescriptionEdited(int row, bool isDI)
{
    QTableWidget* table = isDI ? ui.tableWidget_DI : ui.tableWidget_DO;

    QTableWidgetItem* item = table->item(row, 0);
    if (!item) return;

    // 查询当前反转状态
    bool currentInvert = isDI
        ? m_gtsMgr->configMgr()->diInvertMap().value(row, false)
        : m_gtsMgr->configMgr()->doInvertMap().value(row, false);

    // 构建自定义对话框
    QDialog dlg(this);
    dlg.setWindowTitle(QStringLiteral("编辑IO配置"));
    auto* layout = new QVBoxLayout(&dlg);

    auto* le = new QLineEdit(item->text(), &dlg);
    layout->addWidget(new QLabel(QStringLiteral("功能描述:"), &dlg));
    layout->addWidget(le);

    auto* cb = new QCheckBox(QStringLiteral("反转电平"), &dlg);
    cb->setChecked(currentInvert);
    layout->addWidget(cb);

    auto* bbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
    connect(bbox, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(bbox, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    layout->addWidget(bbox);

    if (dlg.exec() != QDialog::Accepted)
        return;

    QString newText = le->text().trimmed();
    bool newInvert = cb->isChecked();

    if (newText.isEmpty())
        return;

    item->setText(newText);
    m_gtsMgr->configMgr()->setIOConfig(row, newText, newInvert, isDI);
}

void IOWidget::onDOCellDoubleClicked(int row, int col)
{
    if (col == 0)
        onDescriptionEdited(row, false);
}

void IOWidget::onConfigReloaded()
{
    // 重建表格以刷新描述
    InitTableDI();
    InitTableDO();
}
