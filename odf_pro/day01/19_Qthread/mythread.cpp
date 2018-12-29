#include "mythread.h"


//线程在创建的时候 先选择QObject 因为线程不是空间所以不能选择QWidget

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    //很复杂的数据处理需要耗时5s
    sleep(5);

    emit isDone();

}
