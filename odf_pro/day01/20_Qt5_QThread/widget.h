#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void dealSignal();//处理mythread发送过来的信号
    void dealClose();

private slots:
    void on_pubuttonStart_clicked();

    void on_pubuttonStop_clicked();

signals:
    void startThread();//启动子线程的信号

private:
    Ui::Widget *ui;
    MyThread *myT;

    QThread *thread;

};

#endif // WIDGET_H
