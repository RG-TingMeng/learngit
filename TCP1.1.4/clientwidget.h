﻿#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>//通信套接字

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

    QTcpSocket *tcpSocket;//通信套接字

};

#endif // CLIENTWIDGET_H
