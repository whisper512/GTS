#include "MainWnd.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWnd window;
    window.show();
    return app.exec();
}
