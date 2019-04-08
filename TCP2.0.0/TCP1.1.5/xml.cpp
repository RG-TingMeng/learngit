#include <QFile>
#include <QtXml>
#include "xml.h"

Xml::Xml(){}


/**
 * @brief 读取配置文件xml里的数据
 */
void Xml::ReadXml()
{
    QFile file("D:/QT/xml.xml");
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }
    QDomDocument doc;


    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement();
    qDebug()<<root.tagName();

    QDomNodeList list=root.childNodes();

    for(int i=0;i<list.count();i++)
    {
        QDomNode n=list.at(i);

        if(n.nodeName()=="ip"){
            m_ip = n.toElement().text();
            qDebug()<<__LINE__<<__FUNCTION__<<"\n"
                   <<m_ip;
        }
        else if(n.nodeName()=="port")
        {
            m_port = n.toElement().text().toInt();
            qDebug()<<__LINE__<<__FUNCTION__<<"\n"
                   <<m_port;
        }
        else if(n.nodeName()=="localhost")
        {
            m_localHost = n.toElement().text();
            qDebug()<<__LINE__<<__FUNCTION__<<"\n"
                   <<m_localHost;
        }
        else if(n.nodeName()=="database")
        {
            m_dataBase = n.toElement().text();
            qDebug()<<__LINE__<<__FUNCTION__<<"\n"
                   <<m_dataBase;
        }
        else if(n.nodeName()=="username")
        {
            m_userName = n.toElement().text();
            qDebug()<<__LINE__<<__FUNCTION__<<"\n"
                   <<m_userName;
        }
        else if(n.nodeName()=="passwd")
        {
            m_passwd = n.toElement().text();
            qDebug()<<__LINE__<<__FUNCTION__<<"\n"
                   <<m_passwd;
        }
        qDebug()<<n.nodeName()<<":"<<n.toElement().text();
    }
}

/**
 * @brief 获取服务器的ip
 */
QString Xml::getIp()
{
    return m_ip;
}

/**
 * @brief 获取服务器的端口号port
 */
int Xml::getPort()
{
    return m_port;
}

/**
 * @brief 获取本地主机地址
 */
QString Xml::getLocalHost()
{
    return m_localHost;
}

/**
 * @brief 获取对应数据库
 */
QString Xml::getDataBase()
{
    return m_dataBase;
}

/**
 * @brief 获取使用数据库的用户名
 */
QString Xml::getUserName()
{
    return m_userName;
}

/**
 * @brief 获取使用数据库的密码
 */
QString Xml::getPasswd()
{
    return m_passwd;
}
