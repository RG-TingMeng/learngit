#include <QApplication>
#include "clientwidget.h"
#include "serverwidget.h"
#include <QtXml>


void ReadXml()
{
    QFile file("xml.xml");
    if(!file.open(QFile::ReadOnly))
        return;
    QDomDocument doc;

    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement();
    qDebug()<<root.nodeName();
    QDomNode node=root.firstChild();
    while(!node.isNull())
    {
        if(node.isElement())
        {
            QDomElement e=node.toElement();
            qDebug()<<e.tagName()<<" "<<e.attribute("id")<<" "<<e.attribute("time");
            QDomNodeList list=e.childNodes();
            for(int i=0;i<list.count();i++)
            {
                QDomNode n=list.at(i);
                if(node.isElement())
                    qDebug()<<n.nodeName()<<":"<<n.toElement().text();
            }
        }
        node=node.nextSibling();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();

    ReadXml();

    ClientWidget ww;
    ww.show();
    return a.exec();
}


