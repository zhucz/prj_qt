#include "widget.h"
#include "ui_widget.h"

#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);
    //只要定时器启动自动触发timerout()

    connect(myTimer ,&QTimer::timeout, this, &Widget::dealTimerout);

    //分配空间,
    thread = new MyThread(this);

    //在线程中连接信号用传统的方式,不要用lambda表达式
    connect(thread , &MyThread::isDone, this, &Widget::dealDone);

    //当按窗口右上角 的红叉时，窗口发出 destroyed()信号
    connect(this, &Widget::destroyed, this, &Widget::stopThread);

    //以上是Qt4风格的线程处理
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealDone()
{
    qDebug() << "it is over";
    myTimer->stop();//关闭定时器
}

void Widget::stopThread()
{
    //关闭线程
    thread->quit();
    //等待线程处理完手头工作
    thread->wait();
}


void Widget::dealTimerout()
{
    static int i = 0;
    i++;
    //设置LCD的值
    ui->lcdNumber->display(i);
}


void Widget::on_pushButton_clicked()
{
    if(myTimer->isActive() == false){
        myTimer->start(500);
    }

#if 0 //不能这么用

    //模拟这里有一个非常复杂的数据处理，耗时比较长
    QThread::sleep(5);//将来用多线程处理

    //处理完数据后，关闭定时器
    myTimer->stop();
    qDebug() << "over";
#endif

    //启动线程，处理数据
    thread->start();


}
