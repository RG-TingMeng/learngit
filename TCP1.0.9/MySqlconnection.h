#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnect()     /*!<连接数据库>*/
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("student");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法打开数据库"),"无法创建数据库!",QMessageBox::Cancel);
        return false;
    }

#endif // CONNECTION_H
