#pragma once
#include <QString>

QString LightBlue = (R"(
    /* 中央控件背景 – 柔和灰蓝渐变 */
    QWidget {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                      stop:0 #e6eff5, stop:0.5 #dce4ec, stop:1 #e6eff5);
    }
    /* 所有标签文字颜色 – 深色保证对比度 */
    QLabel {
        color: #2c3e50;
        font-size: 13px;
        background: #f0f4f8;
    }
    /* 分组框标题 – 浅蓝色突出 */
    QGroupBox {
        color: #2980b9;
        border: 1px solid #2980b9;
        border-radius: 6px;
        margin-top: 8px;
        font-weight: bold;
        padding-top: 16px;
        background: #f0f4f8;
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        left: 10px;
        padding: 0 4px;
        color: #2980b9;
    }
    /* 单行输入框 – 白色带细边框 */
    QLineEdit {
        background: rgba(255,255,255,255);
        border: 1px solid #bdc3c7;
        border-radius: 4px;
        padding: 3px 6px;
        color: #2c3e50;
        selection-background-color: #3498db;
    }
    /* 下拉框 */
    QComboBox {
        background: #ffffff;
        border: 1px solid #bdc3c7;
        border-radius: 4px;
        padding: 4px 30px 4px 10px;  /* 右侧留出按钮空间 */
        color: #2c3e50;
        min-width: 100px;
    }
    QComboBox::down-arrow {
        image: url(:/StyleSheet/StyleSheetRes/down.png);
        width: 24px;
        height: 24px;
        right: 5px;        /* 在 drop-down 内的位置 */
        background: #f0f4f8;
    }
    QComboBox::drop-down {
        width: 24px;
        background: #f0f4f8;
        border: none;
        subcontrol-origin: padding;
        subcontrol-position: top right;
    }
    QComboBox QAbstractItemView {
        background: #ffffff;
        color: #2c3e50;
        selection-background-color: #3498db;
        selection-color: white;
    }
    /* 按钮 */
    QPushButton {
        background: #f0f4f8;
        border: 1px solid #5dade2;
        color: #2c3e50;
        padding: 6px 18px;
        border-radius: 6px;
    }
    QPushButton:hover {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                      stop:0 #5dade2, stop:1 #2e86c1);
        color: white;
        font-weight: bold;
    }
    QPushButton:pressed {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                      stop:0 #2e86c1, stop:1 #1a6daa);
        color: white;
        font-weight: bold;
    }
    /* 工具栏按钮 – 侧边导航 */
    QToolButton {
        background: #f0f4f8;
        border: 1px solid #5dade2;
        color: #2c3e50;
        padding: 8px 12px;
        border-radius: 4px;
        text-align: left;
    }
    QToolButton:hover {
        background: rgba(52, 152, 219, 40);
        color: #2980b9;
    }
    QToolButton:checked {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                      stop:0 #5dade2, stop:1 #2e86c1);
        color: white;
        font-weight: bold;
    }
    /* 菜单栏 */
    QMenuBar {
        background: #f0f4f8;
        color: #2c3e50;
        border-bottom: 1px solid #bdc3c7;
    }
    QMenuBar::item:selected {
        background: #d6eaf8;
    }
    QMenu {
        background: #ffffff;
        color: #2c3e50;
        border: 1px solid #bdc3c7;
    }
    QMenu::item:selected {
        background: #d6eaf8;
        color: #2c3e50;
    }
)");
