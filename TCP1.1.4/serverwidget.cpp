#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QHostAddress>
#include "student.h"
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

/**
 * @brief serverwidget.cpp主要是服务器这边的连接客户端的一些函数文件
 * @author chentingmeng
 * @version 1.0.7
 * @date 2019.3.29
 */




ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    //设置table widegt表格，选中一行
    ui->tableWidgetStu->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetStu->setSelectionMode(QAbstractItemView::SingleSelection);

    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字，指定父对象，自动回收空间
    tcpServer = new QTcpServer(this);
    //监听
    tcpServer->listen(QHostAddress::Any,1000);
    setWindowTitle("Server 1000");

    connect(tcpServer,&QTcpServer::newConnection,this,&ServerWidget::dealConnect);
    connect(tcpSocket, &QTcpSocket::readyRead,this,&ServerWidget::readInfo);
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void operator <(QString &t_str,int a)
{
    t_str<a;
    return ;
}

void operator == (QString &t_str,int a)
{
    t_str==a;
    return;
}

/**
 * @brief 从通信套接字中取出内容
 */
void ServerWidget::readInfo()
{
    //读取客户端的数据
    QByteArray array = tcpSocket->readAll();

    QString t_str = array;
    //用mid()函数截取数字和字母部分
    QString t_strOther = t_str.mid(1,array.length()-1);
    int t_strIndex = t_str.mid(0,1).toInt();
    QString t_age,t_name;

    if(t_strIndex == 0)
    {
        for(int i=0;i<t_strOther.length();i++)
        {
            //找出读取到的字符串中的字母部分
            if(t_strOther[i]>'a'&&t_strOther[i] <'z')
            {
                t_name.append(t_strOther[i]);
            }
            //找出读取到的字符串中数字部分
            if(t_strOther[i]>'0'&&t_strOther[i] <'9')
            {
                t_age.append(t_strOther[i]);
            }
        }
        ui->tableWidgetStu->setItem(1,0,new QTableWidgetItem(t_name));
        ui->tableWidgetStu->setItem(1,1,new QTableWidgetItem(t_age));

    }else
    {
        for(int i=0;i<t_strOther.length();i++)
        {
            if(t_strOther[i]>'a'&&t_strOther[i] <'z')
            {
                t_name.append(t_strOther[i]);
            }
            if(t_strOther[i]>'0'&&t_strOther[i] <'9')
            {
                t_age.append(t_strOther[i]);
            }
        }
        ui->tableWidgetPro->setItem(1,0,new QTableWidgetItem(t_name));
        ui->tableWidgetPro->setItem(1,1,new QTableWidgetItem(t_age));
    }
    //客户端write window传过来的内容进行显示
    ui->textEditRead->append(array);
}

/**
 * @brief 主动和客户端进行连接并判断是否连接成功
 */
void ServerWidget::dealConnect()
{
    //取出建立好连接的套接字
    tcpSocket = tcpServer->nextPendingConnection();

    //获取对方的IP和端口
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
    //获取编辑区内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发送数据，使用的套接字是tcpSocket
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

}

/**
 * @brief 服务器在历史模式下从MySql中获取学生,程序员的信息到table widget中
 */
void ServerWidget::on_btnSqlOut_clicked()
{
    //历史模式时从数据库中读取到table widget
    QSqlQuery  queryStu,queryPro;
    int t_rowStu = 1,t_rowPro=1;

    //学生的信息
    queryStu.exec("SELECT * FROM student");
    while(queryStu.next())
    {
        QString t_name = queryStu.value(0).toString();
        int t_age = queryStu.value(1).toInt();
        ui->tableWidgetStu->setItem(t_rowStu,0,new QTableWidgetItem(t_name));
        ui->tableWidgetStu->setItem(t_rowStu,1,new QTableWidgetItem(t_age));
    }
    //程序员的信息
    queryPro.exec("SELECT * FROM programmer");
    while(queryPro.next())
    {
        QString t_name = queryPro.value(0).toString();
        int t_age = queryPro.value(1).toInt();
        ui->tableWidgetPro->setItem(t_rowPro,0,new QTableWidgetItem(t_name));
        ui->tableWidgetPro->setItem(t_rowPro,1,new QTableWidgetItem(t_age));
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
