#include "Widget/AdvGTSControllerWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GTSControllerWidget window;
    window.show();
    return app.exec();
}
