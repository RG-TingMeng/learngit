#include "ui_clientwidget.h"
#include <QHostAddress>
#include <QString>
#include "clientwidget.h"
#include "person.h"



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
    ui->textEditRead->setText(QObject::tr("connect success"));//  连接成功
}
void ClientWidget::readInfo()
{
    QString str = tcpSocket->readAll();
    ui->textEditRead->append(str);
}

/**
 * @brief 点击connect后和服务器进行连接
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
    //获取comboBox中对应的索引值
    int t_comboBoxIndex = ui->comboBox->currentIndex();

    QString t_name = ui->lineEditName->text();
    QByteArray  t_strName = t_name.toLatin1();

    int t_age = ui->lineEditAge->text().toInt();
    QString t_str = QString::number(t_age,10);
    QByteArray  t_strAge = t_str.toLatin1();

    QString t_strIn = QString::number(t_comboBoxIndex,10);
    QByteArray t_strIndex = t_strIn.toLatin1();

    int t_sizeofName = t_name.length();
    int t_sizeofAllDate = sizeof(t_strIndex)+sizeof(t_sizeofName)+sizeof(t_strName)+sizeof(t_strAge);

    qDebug()<<__LINE__<<__FUNCTION__<<"\n"
           <<"t_sizeofAdate:"<<t_sizeofAllDate<<"\n";

    Person t_person;
    t_person.setDateLength(t_sizeofAllDate );
    t_person.setComboBoxIndex( t_comboBoxIndex);
    t_person.setNameLength(t_sizeofName);
    t_person.setName(t_name);
    t_person.setAge(t_age);

    QByteArray t_array;
    t_array.append((char *)&t_person,sizeof(t_person));
    tcpSocket->write(t_array);

}
