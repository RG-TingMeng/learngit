/**
 * @brief 客户端声明文件
 * @details 主要是客户端连接服务器的一些函数de文件
 * @author chentingmeng
 * @version 1.0.7
 * @date 2019.3.29
 * @warning
 * @copyright
 * @note
 */

#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_btnConnect_clicked();
    void on_btnSend_clicked();
    void on_btnClose_clicked();

    void dealConnect();
    void readInfo();

    void on_btnAdd_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;

};

#endif // CLIENTWIDGET_H
