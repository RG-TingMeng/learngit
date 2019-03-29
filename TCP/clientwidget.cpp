#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = NULL;
    tcpSocket = new QTcpSocket(this);

    setWindowTitle("Client");

    connect(tcpSocket, &QTcpSocket::connected,this,&ClientWidget::dealConnect);
    connect(tcpSocket, &QTcpSocket::readyRead,this,&ClientWidget::readInfo);

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::dealConnect()
{
    ui->textEditRead->setText("connect success");
}
void ClientWidget::readInfo()
{
    QString str = tcpSocket->readAll();
    ui->textEditRead->append(str);
}

void ClientWidget::on_btnConnect_clicked()
{
    //获取服务器IP和端口
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_btnSend_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    //获取编辑框内容
    QString str = ui->textEditWrite->toPlainText();
    //发送数据
    tcpSocket->write(str.toUtf8().data());
}

void ClientWidget::on_btnClose_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    //主动和对方断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
