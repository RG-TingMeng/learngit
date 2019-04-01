#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnect()     /*!<�������ݿ�>*/
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("student");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("�޷������ݿ�"),"�޷��������ݿ�!",QMessageBox::Cancel);
        return false;
    }

#endif // CONNECTION_H
