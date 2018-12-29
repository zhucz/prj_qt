#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

protected:
    //QThread 的虚函数
    //线程处理虚拟函数
    //不能直接调用，通过start()间接调用
    void run();

signals:
    void isDone();

public slots:
};

#endif // MYTHREAD_H
