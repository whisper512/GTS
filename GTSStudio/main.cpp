#include "Widget/GTSControllerWidget.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Fusion 风格 + 统一调色板
    app.setStyle(QStyleFactory::create("Fusion"));

    QPalette p;
    p.setColor(QPalette::Window,          QColor(240, 244, 248));  // 主窗口浅蓝灰
    p.setColor(QPalette::WindowText,      QColor(44,  62,  80));   // 深色文字
    p.setColor(QPalette::Base,            QColor(255, 255, 255));  // 输入框白底
    p.setColor(QPalette::AlternateBase,   QColor(235, 240, 245));
    p.setColor(QPalette::ToolTipBase,     QColor(255, 255, 255));
    p.setColor(QPalette::ToolTipText,     QColor(44,  62,  80));
    p.setColor(QPalette::Text,            QColor(44,  62,  80));
    p.setColor(QPalette::Button,          QColor(240, 244, 248));
    p.setColor(QPalette::ButtonText,      QColor(44,  62,  80));
    p.setColor(QPalette::BrightText,      Qt::red);
    p.setColor(QPalette::Link,            QColor(41,  128, 185));
    p.setColor(QPalette::Highlight,       QColor(41,  128, 185));  // 选中高亮蓝
    p.setColor(QPalette::HighlightedText, Qt::white);
    app.setPalette(p);

    GTSControllerWidget window;
    window.show();
    return app.exec();
}
