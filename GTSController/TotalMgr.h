#ifndef TOTALMGR_H
#define TOTALMGR_H

#include <QObject>
#include <memory>


class BoardMgr;


// TotalMgr — 总管理器
class TotalMgr : public QObject {
    Q_OBJECT

private:
    bool m_initialized = false;
    std::unique_ptr<BoardMgr> m_board;

public:
    explicit TotalMgr(QObject* parent = nullptr);
    ~TotalMgr();

    bool initialize(short channel = 0);
    void shutdown();
    bool isInitialized() const { return m_initialized; }


    // 板卡管理器
    BoardMgr* board() const { return m_board.get(); }


    void emergencyStop();
    // 获取最近一次错误字符串
    QString lastErrorString() const;

signals:
    // 初始化完成
    void initialized();
    // 已关闭
    void shutdowned();
    // 发生错误
    void errorOccurred(const QString& errorMsg);


};

#endif // TOTALMGR_H
