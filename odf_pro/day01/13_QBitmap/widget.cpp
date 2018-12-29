#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QBitmap>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    //QPixmap
    p.drawPixmap(0,0,200,200,QPixmap("../image/car.jpg"));

    //QBitmap
    p.drawPixmap(200,0,200,200,QBitmap("../image/car.jpg"));

    //QPixmap 加载图片
    QPixmap pixmap;
    pixmap.load("../image/car.jpg");
    p.drawPixmap(0,200,200,200 ,pixmap);

    //QBitmap
    QBitmap bitmap;
    bitmap.load("../image/car.jpg");
    p.drawPixmap(200,200,200,200 ,bitmap);

//绘图设备
//QPixmap  ：针对屏幕进行优化了，和平台相关  （比较常用，不能对图片进行修改）
//QImage   ：和平台无关，可以对图片进行修改，在线程中绘图
//QPicture ：保存绘图的状态，保存为二进制文件



}
