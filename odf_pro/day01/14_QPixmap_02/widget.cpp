#include "widget.h"
#include "ui_widget.h"

#include <QPixmap>
#include <QPainter>
#include <QBrush>

//不在窗口里面绘图 在设备上绘图，所以需要保存

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //绘图设备
    QPixmap pixmap(400,300);

    //把绘图设备给画家
    QPainter p(&pixmap);

    //填充背景色
    p.fillRect(0,0,400,300,QBrush(Qt::white));
    //pixmap.fill(Qt::white);


    p.drawPixmap(0,0,150,150,QPixmap("../Image/car.jpg"));

    //保存图片
    pixmap.save("../pixmap.jpg");
}

Widget::~Widget()
{
    delete ui;
}
