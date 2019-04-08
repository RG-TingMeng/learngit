#include <QApplication>
#include "clientwidget.h"
#include "serverwidget.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();

    ClientWidget ww;
    ww.show();
    return a.exec();
}


