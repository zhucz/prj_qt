#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//方式一  前景色  某一个控件有效  //看不全给一个布局
//    ui->label->setStyleSheet("QLabel{color:green;"
//                             "background-color:red;"
//                             "background-image:url(://Image/car.jpg)"
//                             "}");

//可伸缩的样式  图像裁剪      //设置背景图片
        ui->label->setStyleSheet("QLabel{color:green;"
                                 "background-color:red;"
                                 "border-image:url(://Image/car.jpg) 200 200 200 200 stretch stretch;"
                                 "}");

//方式二 rgb
//    ui->label->setStyleSheet("QLabel{color:rgb(80,90,255);}");



//整控件都这样的样式
//    ui->label->setStyle("QLabel{color:green;"
//                         "background-color:red"
//                          "}");



    ui->pushButton->setStyleSheet("QPushButton{"
                                  "border-image:url(://Image/car.jpg);"
                                  "}"
                                  "QPushButton:hover{"
                                  "border-image:url(://Image/pkq.jpg);"
                                  "}"
                                  "QPushButton:pressed{"
                                  "border-image:url(://Image/car.jpg);"
                                  "}"
                                  );


}

Widget::~Widget()
{
    delete ui;
}
