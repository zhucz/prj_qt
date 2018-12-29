#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCompleter> //用来模糊查询 和字符串列表一起
#include <QStringList> //字符串列表
#include <QMovie> //动画

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Mybutton->setText("123");

    //connect(ui->Mybutton, &QPushButton::clicked, this, &MainWindow::close);

    //QlineEDIT
    QString str = ui->lineEdit->text(); //获取内容
    qDebug() << str;

//设置内容
    ui->lineEdit->setText("123456789");
//设置内容显示间隙
    ui->lineEdit->setTextMargins(25,0,0,0);

//设置内容显示方式
    //ui->lineEdit->setEchoMode(QLineEdit::Password);


//模糊查询
    QStringList list;
    list << "hello" << "How are you" << "hehe";

    QCompleter  *com = new QCompleter(list,this);
    com->setCaseSensitivity(Qt::CaseInsensitive);

    ui->lineEdit->setCompleter(com);


 //QLabel
    ui->labelText->setText("^_^");
    //设置图片
    ui->labelImage->setPixmap(QPixmap("://Image/car.jpg"));

    //让图片自动适应大小
     ui->labelImage->setScaledContents(true);
    ui->labelImage->setMaximumSize(70,70);

     //创建动画
     QMovie *myMovie = new QMovie("://Image/laiwan.gif");
     //设置动画
     ui->labelGif->setMovie(myMovie);
     //启动动画
     myMovie->start();

     ui->labelGif->setScaledContents(true);

     //设置Html
     ui->labelUrl->setText("<h1><a href=\"heeps://www.baidu.com\">  百度一下 </a></h1>");
     ui->labelUrl->setOpenExternalLinks(true);//打开外部链接


     //数码管
     ui->lcdNumber->display(123);

     //进度条
     ui->progressBar->setMinimum(0);//设置最小值
     ui->progressBar->setMaximum(200);//设置最大值
     ui->progressBar->setValue(100);//设置当前值

    //WebView  将网页上的内容显示到这里来
     //我的QT里面没有这个控件
     //ui->webView->load(QUrl("http://www.baidu.com"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_change_clicked()
{
    static int i = 0;

    ui->stackedWidget->setCurrentIndex(++i % 4);
}
