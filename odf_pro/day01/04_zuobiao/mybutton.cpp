#include "mybutton.h"
#include <QDebug>

Mybutton::Mybutton(QWidget *parent) : QPushButton(parent)
{

}


Mybutton::~Mybutton()
{
    qDebug() << "按钮被释放";
}
