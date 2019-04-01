#include "serverwidget.h"
#include <QApplication>
#include "clientwidget.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

/**
 * @brief 设置本地ip,数据库名,数据库用户名,数据库登录密码并启动MySql
 * @return 判断数据库是否打开
 */
static bool createConnect()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("course");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("Don't open MySql!"),"Don't  create MySql!",QMessageBox::Cancel);
        return false;
    }

 }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     if(!createConnect())
         return 0;
    ServerWidget w;
    w.show();

    ClientWidget ww;
    ww.show();
      return a.exec();
}
