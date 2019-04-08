#include "ui_serverwidget.h"
#include <QHostAddress>
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include "serverwidget.h"
#include "person.h"
#include "xml.h"



ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    ui->tableWidgetStu->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetStu->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetStu->setRowCount(5);
    ui->tableWidgetPro->setRowCount(5);
    ui->tableWidgetPro->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetPro->setSelectionMode(QAbstractItemView::SingleSelection);

    Xml t_xml;
    t_xml.ReadXml();
    ui->lineEditLocaHost->setText(t_xml.getLocalHost());
    qDebug()<<"t_xml.getLocalHost:"<<t_xml.getLocalHost();
    ui->lineEditDateBs->setText(t_xml.getDataBase());
    ui->lineEditUseName->setText(t_xml.getUserName());
    ui->lineEditPassWd->setText(t_xml.getPasswd());

    tcpServer = NULL;
    tcpSocket = NULL;

    t_RowStu = 0;
    t_RowPro = 0;

    t_currStuPage = 0;
    t_currProPage = 0;

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,1000);
    setWindowTitle("Server 1000");

    connect(tcpServer,&QTcpServer::newConnection,this,&ServerWidget::dealConnect);
    connect(tcpSocket, &QTcpSocket::readyRead,this,&ServerWidget::readInfo);
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

/**
 * @brief 从通信套接字中取出内容
 */
void ServerWidget::readInfo()
{
    QByteArray t_array = tcpSocket->readAll();
    ui->textEditRead->append(t_array);

    Person *t_person = (Person *)t_array.data();
    //判断第一个int数据字节是否完整
    if(sizeof(t_person->getDateLength()) >= 4 )
    {
        qDebug()<<__LINE__<<__FUNCTION__<<"\n"
               <<"t_person.dateLength:"<<t_person->getDateLength();
        int sizeofAllDate = sizeof(t_person->getComboBoxIndex())+sizeof(t_person->getNameLength())+sizeof(t_person->getAge())+sizeof(t_person->getName());
        qDebug()<<__LINE__<<__FUNCTION__<<"\n"
               <<"sizeofAllDate:"<<sizeofAllDate;
        qDebug()<<__LINE__<<__FUNCTION__<<"\n"
               <<"age:"<<t_person->getAge();

        //判断数据是否丢失
        if(t_person->getDateLength() == sizeofAllDate)
        {
            if(t_person->getComboBoxIndex()==0)
            {
                int t_countStuRow = t_RowStu++;
                int t_age = t_person->getAge();
                QString t_strAge = QString::number(t_age,10);

                ui->tableWidgetStu->setItem(t_countStuRow,0,new QTableWidgetItem(t_person->getName()));
                ui->tableWidgetStu->setItem(t_countStuRow,1,new QTableWidgetItem(t_strAge));
                const Person t_per = *t_person;
                t_stuList.push_back(t_per);
            }
            else
            {
                int t_countProRow = t_RowPro++;
                int t_age = t_person->getAge();
                QString t_strAge = QString::number(t_age,10);

                ui->tableWidgetPro->setItem(t_countProRow,0,new QTableWidgetItem(t_person->getName()));
                ui->tableWidgetPro->setItem(t_countProRow,1,new QTableWidgetItem(t_strAge));
                const Person t_per = *t_person;
                t_proList.push_back(t_per);
            }
        }
    }
}

/**
 * @brief 主动和客户端进行连接并判断是否连接成功
 */
void ServerWidget::dealConnect()
{
    tcpSocket = tcpServer->nextPendingConnection();

    QString ip = tcpSocket->peerAddress().toString();
    qint16 port = tcpSocket->peerPort();

    //TODO：中文乱码
    QString temp = QString("[%1:%2],connect successfully").arg(ip).arg(port);

    ui->textEditRead->setText(temp);
    connect(tcpSocket, &QTcpSocket::readyRead,this,&ServerWidget::readInfo);

}

/**
 * @brief 点击"send"按钮发送数据给客户端
 */
void ServerWidget::on_btnSend_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    QString str = ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

/**
 * @brief 点击"关闭"按钮，主动和客户端断开连接
 */
void ServerWidget::on_btnClose_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
}


/**
 * @brief 获取table Widget中选中行然后存入MySql中
 */
void ServerWidget::on_btnToSql_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        int t_curRow = ui->tableWidgetStu->currentRow();
        QString t_strName = ui->tableWidgetStu->item(t_curRow,0)->text();
        QString t_strAge= ui->tableWidgetStu->item(t_curRow,1)->text();
        int t_age = t_strAge.toInt();
        QSqlQuery query;
        //用oracle语法格式把数据插入MySql中
        query.prepare("INSERT INTO student (name,age)"
                      "VALUES(:name,:age)");
        query.bindValue(":name",t_strName);
        query.bindValue(":age",t_age);
        query.exec();
    }
    else{
        int t_curRow = ui->tableWidgetPro->currentRow();
        QString t_strName = ui->tableWidgetPro->item(t_curRow,0)->text();
        QString t_strAge= ui->tableWidgetPro->item(t_curRow,1)->text();
        int t_age = t_strAge.toInt();
        QSqlQuery query;
        //用oracle语法格式把数据插入MySql中
        query.prepare("INSERT INTO programmer (name,age)"
                      "VALUES(:name,:age)");
        query.bindValue(":name",t_strName);
        query.bindValue(":age",t_age);
        query.exec();
    }
}

/**
 * @brief 服务器在历史模式下从MySql中获取学生,程序员的信息到table widget中
 */
void ServerWidget::on_btnSqlOut_clicked()
{
    QSqlQuery  queryStu,queryPro;
    int t_rowStu = 0,t_rowPro=0;

    if(ui->tabWidget->currentIndex()==0)
    {   //学生的信息
        queryStu.exec("SELECT * FROM student");
        while(queryStu.next())
        {
            QString t_name = queryStu.value(0).toString();
            int t_age = queryStu.value(1).toInt();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetStu->setItem(t_rowStu,0,new QTableWidgetItem(t_name));
            ui->tableWidgetStu->setItem(t_rowStu,1,new QTableWidgetItem(t_strAge));
            t_rowStu++;
        }
    }
    else
    {    //程序员的信息
        queryPro.exec("SELECT * FROM programmer");
        while(queryPro.next())
        {
            QString t_name = queryPro.value(0).toString();
            int t_age = queryPro.value(1).toInt();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetPro->setItem(t_rowPro,0,new QTableWidgetItem(t_name));
            ui->tableWidgetPro->setItem(t_rowPro,1,new QTableWidgetItem(t_strAge));
            t_rowPro++;
        }
    }
}

/**
 * @brief 设置本地ip,数据库名,数据库用户名,数据库登录密码并启动MySql
 */
void ServerWidget::on_pushButton_clicked()
{
    QString t_lineEditLocaHost = ui->lineEditLocaHost->text();
    QString t_lineEditDateBs = ui->lineEditDateBs->text();
    QString t_lineEditUseName = ui->lineEditUseName->text();
    QString t_lineEditPassWd = ui->lineEditPassWd->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(t_lineEditLocaHost);
    db.setDatabaseName(t_lineEditDateBs);
    db.setUserName(t_lineEditUseName);
    db.setPassword(t_lineEditPassWd);
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("Don't open MySql!"),"Don't  create MySql!",QMessageBox::Cancel);
        return;
    }
}

/**
 * @brief 定义翻上一页
 */
void ServerWidget::on_btnTurnUp_clicked()
{

    if(ui->tabWidget->currentIndex()==0)
    {
        if(t_currStuPage==0)
            return ;
        t_currStuPage -=5;
        int t_stuR = 0;
        for(int i=t_currStuPage;i<t_currStuPage+5;i++)
        {
            int t_age = t_stuList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetStu->setItem(t_stuR,0,new QTableWidgetItem(t_stuList.at(i).getName()));
            ui->tableWidgetStu->setItem(t_stuR,1,new QTableWidgetItem(t_strAge));
            t_stuR++;
        }
    }
    else
    {
        t_currProPage -=5;
        int t_proR = 0;
        for(int i=t_currProPage;i<t_currProPage+5;i++)
        {
            int t_age = t_proList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetPro->setItem(t_proR,0,new QTableWidgetItem(t_proList.at(i).getName()));
            ui->tableWidgetPro->setItem(t_proR,1,new QTableWidgetItem(t_strAge));
            t_proR++;
        }
    }
}

/**
 * @brief 定义翻下一页
 */
void ServerWidget::on_btnTurnDown_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        t_currStuPage +=5;
        int t_stuR=0;
        for(int i=t_currStuPage;i<t_currStuPage+5;i++)
        {
            int t_age = t_stuList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetStu->setItem(t_stuR,0,new QTableWidgetItem(t_stuList.at(i).getName()));
            ui->tableWidgetStu->setItem(t_stuR,1,new QTableWidgetItem(t_strAge));
            t_stuR++;
        }
    }
    else
    {
        t_currProPage +=5;
        int t_proR = 0;
        for(int i=t_currProPage;i<t_currProPage+5;i++)
        {
            int t_age = t_proList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetPro->setItem(t_proR,0,new QTableWidgetItem(t_proList.at(i).getName()));
            ui->tableWidgetPro->setItem(t_proR,1,new QTableWidgetItem(t_strAge));
            t_proR++;
        }
    }
}

/**
 * @brief 翻到首页
 */
void ServerWidget::on_btnFirst_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        t_currStuPage =0;
        int t_stuR=0;
        for(int i=t_currStuPage;i<t_currStuPage+5;i++)
        {
            int t_age = t_stuList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetStu->setItem(t_stuR,0,new QTableWidgetItem(t_stuList.at(i).getName()));
            ui->tableWidgetStu->setItem(t_stuR,1,new QTableWidgetItem(t_strAge));
            t_stuR++;
        }
    }
    else
    {
        t_currProPage = 0;
        int t_proR =0;
        for(int i=t_currProPage;i<t_currProPage+5;i++)
        {
            int t_age = t_proList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetPro->setItem(t_proR,0,new QTableWidgetItem(t_proList.at(i).getName()));
            ui->tableWidgetPro->setItem(t_proR,1,new QTableWidgetItem(t_strAge));
            t_proR++;
        }
    }
}

/**
 * @brief 翻到末页
 */
void ServerWidget::on_btnEnd_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        t_currStuPage +=5;                 //TODO:末页还没实现
        int t_stuR=0;
        for(int i=t_currStuPage;i<t_currStuPage+5;i++)
        {
            int t_age = t_stuList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetStu->setItem(t_stuR,0,new QTableWidgetItem(t_stuList.at(i).getName()));
            ui->tableWidgetStu->setItem(t_stuR,1,new QTableWidgetItem(t_strAge));
            t_stuR++;
        }
    }else
    {
        t_currProPage +=5;
        int t_proR =0;
        for(int i=t_currProPage;i<t_currProPage+5;i++)
        {
            int t_age = t_proList.at(i).getAge();
            QString t_strAge = QString::number(t_age,10);
            ui->tableWidgetPro->setItem(t_proR,0,new QTableWidgetItem(t_proList.at(i).getName()));
            ui->tableWidgetPro->setItem(t_proR,1,new QTableWidgetItem(t_strAge));
            t_proR++;
        }
    }
}

/**
 * @brief lineEditPasswd输入框中的字符串采用暗文显示
 */
void ServerWidget::on_lineEditPassWd_textEdited(const QString &arg1)
{
    ui->lineEditPassWd->setEchoMode(QLineEdit::Password);
}
