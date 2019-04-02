#include "serverwidget.h"
#include <QApplication>
#include "clientwidget.h"
#include "xml.h"
#include<QTreeWidget>
#include<QXmlStreamReader>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList args = QApplication::arguments();
    QTreeWidget treeWidget;
    XmlStreamReader reader(&treeWidget);
    for(int i=1;i<args.count();i++)
    reader.readFile(args[i]);

    ServerWidget w;
    w.show();

    ClientWidget ww;
    ww.show();
      return a.exec();
}
