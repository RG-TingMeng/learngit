#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QHostAddress>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字，指定父对象，自动回收空间
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,6666);//监听

    setWindowTitle("服务器：6666");

    connect(tcpServer,&QTcpServer::newConnection,this,&ServerWidget::dealConnect);
    connect(tcpSocket, &QTcpSocket::readyRead,this,&ServerWidget::readInfo);
}

ServerWidget::~ServerWidget()
{
    delete ui;
}
void ServerWidget::readInfo()
{
    //从通信套接字中取出内容
    QByteArray array = tcpSocket->readAll();
    ui->textEditRead->append(array);
}

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
