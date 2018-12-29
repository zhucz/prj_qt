#include "widget.h"
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>




Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(800,600);
    QPushButton *button = new QPushButton("^_^",this);

    button->setGeometry(100,100,200,200);

    //qt 4
    //connect(button, SIGNAL(clicked(bool)), this, SLOT(close()));

    //qt 5
    //connect(button, &QPushButton::clicked, this, &Widget::close);

/*
 * 信号和槽,信号类比于短信，槽类比于接收短信的手机
 * 1.信号：普通函数(signals:),只需声明无需实现
 * 2.槽函数：Qt5 类中的任意成员函数，静态函数，全局函数,lambda表达式
 * 3.信号和槽可以使用Qt内部定义好的，也可以自定义
 * 4.信号和槽是没有返回值，但是可以有参数
 * 5.信号和槽的参数列表顺序必须一致
 * void sigl(int, double, char);
 * void slot(int, double, char);
 * 6.信号和槽的参数个数可以不一样
 * 信号的参数个数可以大于槽函数参数的个数
 * 槽函数参数的个数不可以大于信号参数的个数
*/


    connect(button ,&QPushButton::clicked,
            [=]()
            {
              button->setText("123");
            }

            );
}

Widget::~Widget()
{

}
