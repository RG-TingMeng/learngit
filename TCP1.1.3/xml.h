#ifndef XML_H
#define XML_H

#include<QXmlStreamReader>
#include <QTreeWidget>
class XmlStreamReader
{
public:
    XmlStreamReader(QTreeWidget *tree);
    bool readFile(const QString &fileName);
private:
    void readTextMembers();
    void readEntryMembers();
    void readIp();
    void readPort();
    void skipUnknownElement();

    QTreeWidget *treeWidget;
    QXmlStreamReader  reader;

}
#endif // XML_H
