#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPushButton>
#include <QDebug>
#include "mybutton.h"

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    move(100,100);

    ui->setupUi(this);



    QPushButton *b1 = new QPushButton(this);
    b1->setText("^_^");
    b1->move(100,100);
    b1->resize(200,100);

    QPushButton *b2 = new QPushButton(b1);
    b2->move(10,10);
    b2->setText("@_@");


    Mybutton *b3 = new Mybutton(this);
    b3->setText("123");

    //1)指定父对象后  2)直接或间接继承与QObject
    //子对象如果是动态分配空间的new ,不需要手动释放delete
    //系统会自动释放

}

myWidget::~myWidget()
{
    delete ui;


}
