#include "serverwidget.h"
#include <QApplication>
#include "clientwidget.h"
//#include "xml.h"
//#include<QXmlStreamReader>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QStringList args = QApplication::arguments();   //TODO:xml�ļ�Ƕ�����һ��qfileDevice.h�ļ����ұ���
//    QTreeWidget treeWidget;
//    XmlStreamReader reader;
//    for(int i=1;i<args.count();i++)
//    reader.readFile();

    ServerWidget w;
    w.show();

    ClientWidget ww;
    ww.show();
      return a.exec();
}
