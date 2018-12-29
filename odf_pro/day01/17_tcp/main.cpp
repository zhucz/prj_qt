#include "widget.h"
#include <QApplication>
#include "clienwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


    ClienWidget w2;
    w2.show();

    return a.exec();
}
