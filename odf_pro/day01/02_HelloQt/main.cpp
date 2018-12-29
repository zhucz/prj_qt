#include <QApplication>
#include <QWidget>//窗口控件基类
#include <QPushButton>


int main(int argc,char **argv)
{
    QApplication app(argc,argv);
    QWidget w;

    w.setWindowTitle("车辆智能管系统");


    QPushButton b1;
    b1.setText("^_^");
    b1.setParent(&w);  //指定父对象
    b1.move(100,100);   //移动坐标

    /*
     * 如果不指定父对象，对象和对象(窗口和窗口)没有关系，独立的
     * A指定B为他的父对象，A放在B里面
     * 指定父对象，有两种方式：
     * 1）setParent
     * 2）通过构造函数传参
     * 指定父对象，只需要父对象显示，上面的子对象自动显示
    */



    QPushButton b2(&w);//通过构造函数传参
    b2.setText("abc");

    w.show();
    app.exec();
    return 0;
}
