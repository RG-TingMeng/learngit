#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>//监听套接字
#include <QTcpSocket>//通信套接字
#include "student.h"
namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();
    void ServerWidget::add_Object_tableWidget();
     Student & operator =(Student &stu);

private slots:
    void on_btnSend_clicked();

    void on_btnClose_clicked();
    void dealConnect();
    void readInfo();

    void on_btnToSql_clicked();

private:
    Ui::ServerWidget *ui;

    QTcpServer *tcpServer;//监听套接字
    QTcpSocket *tcpSocket;//通信套接字

};

#endif // SERVERWIDGET_H
