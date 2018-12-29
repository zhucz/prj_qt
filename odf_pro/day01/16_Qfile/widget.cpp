#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonread_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "TXT(*.txt)");

    if(path.isEmpty() == false){
        //创建文件对象
        QFile file(path);

        //打开文件以只读方式
        bool isOK = file.open(QIODevice::ReadOnly);
        if(isOK == true){
            //开始读文件并显示
            QByteArray array = file.readAll();
            ui->textEdit->setText(QString(array));
        }
        //关闭文件
        file.close();
    }
}

void Widget::on_pushButton_2_clicked()
{
    //新建路径名
    QString path = QFileDialog::getSaveFileName(this, "save", "../", "TXT(*.txt)");
    if(path.isEmpty() == false){
        QFile file;// 创建文件对象
        //关联文件名字
        file.setFileName(path);

        //打开文件，只写
        bool isOK = file.open(QIODevice::WriteOnly);
        if(isOK == true){
            //获取编辑区内容
            QString str = ui->textEdit->toPlainText();
            //写文件
            //QString 转换成 QByteArray
            //file.write(str.toUtf8());

            //QString -> c++ strign -> char *

            //file.write(str.toStdString().data());

            //转换为本地平台编码
            file.write(str.toLocal8Bit());

            //QString -> QByteArray
            QString buf = "123";
            QByteArray a = buf.toUtf8();//中文
            a = buf.toLocal8Bit();//本地编码

            //QByteArray  -> char *
            char *b = a.data();

            //char * -> QByteArray
            char *p = "abc";
            QString c = QString(p);


        }
        file.close();
    }

}
