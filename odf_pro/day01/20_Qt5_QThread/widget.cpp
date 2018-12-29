#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //动态分配空间，不能指定父对象
    myT = new MyThread;

    //创建子线程
    thread = new QThread(this);

    //把自定义的线程加入到子线程中
    myT->moveToThread(thread);


    connect(myT, &MyThread::mySignal, this, &Widget::dealSignal);

    qDebug() << "主线程号： " << QThread::currentThread();

    connect(this, &Widget::startThread,  myT, &MyThread::myTimout, Qt::QueuedConnection);

    connect(this, &Widget::destroyed, this, &Widget::dealClose);


    // 线程处理函数内部，不允许操作图形界面

    //connect()第五个参数的作用，连接方式：默认，队列，直接
    //多线程时才有意义
    //默认的时候
    //如果是多线，默认使用队列
    //如果是单线程，默认使用直接方式
    //队列：槽函数所在的线程和信号接收者一样
    //直接：槽函数所在线程和发送者一样


}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealClose()
{
    on_pubuttonStop_clicked();//槽函数就是函数可以直接调用
    delete myT;//关闭的时候关闭myT因为他没有指定父对象
}

void Widget::dealSignal()
{
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);
}

void Widget::on_pubuttonStart_clicked()
{
    if(thread->isRunning() == true){
        return;
    }

    //启动线程，大师没有线程处理函数
    thread->start();
    myT->setFlag(false);

    //不能直接调用线程处理函数
    //直接调用，导致，线程处理函数和主线程在同一个线程
    //myT->myTimout();


    //只能通过 signal - slot 方式调用
    emit startThread();



}

void Widget::on_pubuttonStop_clicked()
{
    if(thread->isRunning() == false){
        return;
    }
    //这样也停不了，这两个最好一起使用
//    thread->quit();
//    thread->wait();

    myT->setFlag(true);
    thread->quit();
    thread->wait();

}
