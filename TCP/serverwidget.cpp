#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QHostAddress>
#include "student.h"

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

    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字，指定父对象，自动回收空间
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,1000);//监听

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
    QByteArray array = tcpSocket->readAll();
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

    QString temp = QString("[%1:%2],连接成功").arg(ip).arg(port);

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

Student &Student::operator =(Student &stu)
{
    this->m_name = stu.m_name;
    this->m_age = stu.m_age;
    return *this;
}

/**
 * @brief 添加对象到服务器中的table Widget中的表格中
 */
void ServerWidget::add_Object_tableWidget()
{
//    Student t_stuRead;
//    t_stuRead = tcpSocket->read();
//    //将对象信息放入table Widget中
//    ui->tableWidgetStu->setItem(1,0,t_stuRead.getName());
//    ui->tableWidgetStu->setItem(1,1,t_stuRead.getAge());
}
