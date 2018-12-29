#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //去窗口表框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);


}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,200,200,QPixmap("../Image/car.jpg"));

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton){
        move(event->globalPos() - p);

    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        //如果是右键
        close();
    }else if(event->button() == Qt::LeftButton){
        //求坐标差值
        //当前点击坐标 - 窗口坐下角坐标
        p = event->globalPos() - this->frameGeometry().topLeft();
    }
}


