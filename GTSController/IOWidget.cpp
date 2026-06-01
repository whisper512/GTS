#include <QTimer>

#include "IOWidget.h"
#include "GTSControllerWidget.h"
#include "TotalMgr.h"

CIOWidget::CIOWidget(QWidget *parent,CTotalMgr* mgr)
	: QWidget(parent)
	, m_pTotalMgr(mgr)
{
	ui.setupUi(this);
	m_pGTSControllerWidget = qobject_cast<GTSControllerWidget*>(parent);

	InitUI();
	connectPrivateSignal();

}

CIOWidget::~CIOWidget()
{
}

void CIOWidget::InitUI()
{
	QTimer::singleShot(0, this, [this]() {
        InitTableDI();
        InitTableDO();
		
		});
}

void CIOWidget::InitTableDI()
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
}

void CIOWidget::InitTableDO()
{
    const Block blocks[] = {
        {  0,  8, QStringLiteral("伺服使能0xF")      },
        {  8,  8, QStringLiteral("报警清除0xFF")     },
        { 16, 16, QStringLiteral("通用输出0xFFFF")   },
    };

    InitTableCommon(ui.tableWidget_DO, 32, blocks, sizeof(blocks) / sizeof(blocks[0]));
}

void CIOWidget::InitTableCommon(QTableWidget* table, int totalRows,
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
            stsItem->setForeground(Qt::gray);
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
}


void CIOWidget::connectPrivateSignal()
{

}

void CIOWidget::RefreshTable(QTableWidget* table, const std::vector<int>& status)
{
    for (int i = 0; i < (int)status.size(); ++i) {
        QTableWidgetItem* item = table->item(i, 2);
        if (!item) continue;
        if (status[i]) {
            item->setText(QStringLiteral("● 开"));
            item->setForeground(Qt::green);
        }
        else {
            item->setText(QStringLiteral("● 关"));
            item->setForeground(Qt::gray);
        }
    }
}
void CIOWidget::onDIUpdated(const stuDI& di)
{
    RefreshTable(ui.tableWidget_DI, di.toFlatVector());
}
void CIOWidget::onDOUpdated(const stuDO& dout)
{
    RefreshTable(ui.tableWidget_DO, dout.toFlatVector());
}