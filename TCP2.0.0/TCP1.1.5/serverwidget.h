/**
 * @brief 服务器声明文件
 * @details 主要是服务器这边的连接客户端的一些函数文件
 * @author chentingmeng
 * @version 1.0.7
 * @date 2019.3.29
 * @warning
 * @copyright
 * @note
 */

#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include "person.h"


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

private slots:
    void on_btnSend_clicked();
    void on_btnClose_clicked();

    void dealConnect();
    void readInfo();

    void on_btnToSql_clicked();
    void on_btnSqlOut_clicked();
    void on_pushButton_clicked();
    void on_btnTurnUp_clicked();

    void on_btnTurnDown_clicked();

    void on_btnFirst_clicked();

    void on_btnEnd_clicked();

    void on_lineEditPassWd_textEdited(const QString &arg1);

private:
    Ui::ServerWidget *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    int  t_RowStu;
    int  t_RowPro;
    int  t_currStuPage;
    int  t_currProPage;

    QList<Person> t_stuList;
    QList<Person> t_proList;

};

#endif // SERVERWIDGET_H
