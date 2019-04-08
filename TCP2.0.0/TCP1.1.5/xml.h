#ifndef XML_H
#define XML_H


class  Xml
{
public:
    Xml();
    void ReadXml();
    int getPort();

    QString getIp();
    QString getLocalHost();
    QString getDataBase();
    QString getUserName();
    QString getPasswd();

private:
    int m_port;

    QString m_ip;
    QString m_localHost;
    QString m_dataBase;
    QString m_userName;
    QString m_passwd;


};

#endif // XML_H
