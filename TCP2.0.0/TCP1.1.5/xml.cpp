#include <QFile>
#include <QtXml>
#include "xml.h"

Xml::Xml(){}


/**
 * @brief ��ȡ�����ļ�xml�������
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
 * @brief ��ȡ��������ip
 */
QString Xml::getIp()
{
    return m_ip;
}

/**
 * @brief ��ȡ�������Ķ˿ں�port
 */
int Xml::getPort()
{
    return m_port;
}

/**
 * @brief ��ȡ����������ַ
 */
QString Xml::getLocalHost()
{
    return m_localHost;
}

/**
 * @brief ��ȡ��Ӧ���ݿ�
 */
QString Xml::getDataBase()
{
    return m_dataBase;
}

/**
 * @brief ��ȡʹ�����ݿ���û���
 */
QString Xml::getUserName()
{
    return m_userName;
}

/**
 * @brief ��ȡʹ�����ݿ������
 */
QString Xml::getPasswd()
{
    return m_passwd;
}
