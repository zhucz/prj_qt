#include "widget.h"
#include <QApplication>
#include <QMessageBox>
#include "thread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    //thread *mythread = new thread();
    //mythread->start();

    return a.exec();
}
