#include "clientwidget.h"
#include "ui_clientwidget.h"
#include "student.h"
#include <QHostAddress>

/**
 * @brief ClientWidget.cpp主要是客户端连接服务器的一些函数文件
 * @author chentingmeng
 * @version 1.0.7
 * @date 2019.3.29
 */
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

/**
 * @brief 显示与服务器连接成功
 */
void ClientWidget::dealConnect()
{
    ui->textEditRead->setText("connect success");
}
void ClientWidget::readInfo()
{
    QString str = tcpSocket->readAll();
    ui->textEditRead->append(str);
}

/**
 * @brief 和服务器主动进行连接
 */
void ClientWidget::on_btnConnect_clicked()
{
    //获取服务器IP和端口
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

/**
 * @brief 点击"send"按钮进行发送消息给服务器
 */
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

/**
 * @brief 点击"关闭"按钮时的，客户端主动断开与服务器连接
 */
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

/**
 * @brief 将comboBox中添加的对象发送给服务器
 */
void ClientWidget::on_btnAdd_clicked()
{
    int t_comboBoxIndex = ui->comboBox->currentIndex();
    QString t_name = ui->lineEditName->text();
    int t_age = ui->lineEditAge->text().toInt();

//    Student t_stu;
//    t_stu.setName(t_name);
//    t_stu.setAge(t_age);

    //将学生对象发送过去
//    tcpSocket->write((char *)&t_stu,sizeof(t_stu));

}
