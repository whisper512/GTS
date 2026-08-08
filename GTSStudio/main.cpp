#include "Widget/GTSControllerWidget.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GTSControllerWidget window;
    window.show();
    return app.exec();
}
