#ifndef MYLABLE_H
#define MYLABLE_H

#include <QLabel>

class Mylable : public QLabel
{
    Q_OBJECT
public:
    explicit Mylable(QWidget *parent = 0);

protected:
    //鼠标点击事件
    void mousePressEvent(QMouseEvent *ev);//任何一个都不能自己写因为是虚函数
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *ev);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *ev);
    //进入窗口区域
    void enterEvent(QEvent *event);
    //离开窗口区域
    void leaveEvent(QEvent *event);

signals:

public slots:
};

#endif // MYLABLE_H
