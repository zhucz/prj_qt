#include "mylable.h"
#include <QMouseEvent>
#include <QDebug>

Mylable::Mylable(QWidget *parent) : QLabel(parent)
{
    //设定默认追踪鼠标
    this->setMouseTracking(true);
}


void Mylable::mousePressEvent(QMouseEvent *ev)
{
    int i = ev->x();
    int j = ev->y();

    //c++ sprinf
    /*
     * QString str = QString("abc %1 ^_^ %2").arg(123).arg("make");
     * str = abc 123 ^_^ make
     */

    if(ev->button() == Qt::LeftButton){
        qDebug() << "左键被按下";

    }else if (ev->button() == Qt::RightButton){
        qDebug() << "右键被按下";
    }else if (ev->button() == Qt::MidButton){
        qDebug() << "中间键被按下";
    }


    QString text = QString("<center><h1>Mouse Press:(%1, %2)</h1> </center>")
            .arg(i).arg(j);

    this->setText(text);

}

void Mylable::mouseReleaseEvent(QMouseEvent *ev)
{
    QString text = QString("<center><h1>Mouse Release:(%1, %2)</h1> </center>")
            .arg(ev->x()).arg(ev->y());

    this->setText(text);

}

void Mylable::mouseMoveEvent(QMouseEvent *ev)
{
    QString text = QString("<center><h1>Mouse Move:(%1, %2)</h1> </center>")
            .arg(ev->x()).arg(ev->y());

    //this->setText(text);
}


void Mylable::enterEvent(QEvent *event)
{
    QString text = QString("<center><h1>Mouse Enter</h1> </center>");

    this->setText(text);
}

void Mylable::leaveEvent(QEvent *event)
{
    QString text = QString("<center><h1>Mouse leave</h1> </center>");

    this->setText(text);

}

