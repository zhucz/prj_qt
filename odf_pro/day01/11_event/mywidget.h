#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mybutton.h"

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

protected:
    //键盘按下事件
    void keyPressEvent(QKeyEvent *event);
    //定时器事件
    void timerEvent(QTimerEvent *event);

    void mousePressEvent(QMouseEvent *event);

    //关闭事件
    void closeEvent(QCloseEvent *event);

    //重写event事件
    bool event(QEvent *event);

    //事件过滤器
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MyWidget *ui;
    int timerId;
    int timerId2;
};

#endif // MYWIDGET_H
