#include <QTimer>
#include "ConfigWidget.h"

CConfigWidget::CConfigWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	InitConfigWidget();
}

CConfigWidget::~CConfigWidget()
{}

void CConfigWidget::InitConfigWidget()
{
	QTimer::singleShot(100, this, [this]() {

		});
	connectSignalsAndSlots();

}

void CConfigWidget::connectSignalsAndSlots()
{
}


