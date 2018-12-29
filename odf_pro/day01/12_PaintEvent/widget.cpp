#include "widget.h"
#include "ui_widget.h"

#include <QPainter> //是一个画家
#include <QPen>     //是一个画笔
#include <QBrush>   //是一个画刷



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    x = 0;
}

Widget::~Widget()
{
    delete ui;
}

//该函数自动调用，只要窗口改变
void Widget::paintEvent(QPaintEvent *event)
{
//方式一
    //QPainter p(this);

//方式二
    QPainter p;//创建画家对象
    p.begin(this);//指定当前窗口为绘图设备
    //绘图操作
    //p.drawxx();

//画背景图
//方式一
   // p.drawPixmap(0, 0, width(), height(), QPixmap("../image/car.jpg"));

//方式二
   // p.drawPixmap(rect(), QPixmap("../image/car.jpg"));

//定义画笔
    QPen pen;
    pen.setWidth(5);//设置线宽
   // pen.setColor(Qt::red);
    pen.setColor(QColor(14, 9, 234));//rgb设置颜色
    pen.setStyle(Qt::DashLine);//设置风格


//把画笔交给画家
   p.setPen(pen);

//画直线
    p.drawLine(50,50,250,50);
    p.drawLine(50,50,50,250);

//创建画刷对象 用于对闭合图形填充颜色
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::Dense1Pattern);
//把画刷交给画家
    p.setBrush(brush);



//画矩形
    p.drawRect(200,200,100,50);

//画圆
    p.drawEllipse(QPoint(150,150),50,25);


//画皮卡丘
    p.drawPixmap(x, 180, 40, 40,  QPixmap("../image/car.jpg"));


    p.end();
}


void Widget::on_pushButton_clicked()
{
    x += 20;
    if(x > width()){
        x = 0;
    }
    //手动刷新窗口，让窗口重绘,整个窗口重绘
    //update() 千万不能放到 paintEvent（）
    //绘图不要做太复杂的数据处理
    //先画背景在画线
    update();//间接调用paintEvent()
}
