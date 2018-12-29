#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QTime>
#include <QTimer>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    timer->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(Graph_Show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Graph_Show()
{

    QTime t;
    t=QTime::currentTime();
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    n=qrand()%50;
    Graph_Show(ui->widget);
}

void MainWindow::Graph_Show(QCustomPlot *CustomPlot)
{
    QVector<double> temp(100);
    QVector<double> temp1(100);
     QVector<double> temp2(100);

   srand( (unsigned)time(NULL) );//设置一个随机函数
    for(int i=0;i<100;i++)
    {
        num1[i]=rand()%101;
        num2[i] =rand()%101+100 ;
    }
    for(int i=0;i<100;i++)
    {
        temp[i] = i;
        temp1[i] =num1[i];
        temp2[i]=num2[i];
    }
   //设置画布颜色
    QLinearGradient plotGradient;
    //lotGradient.setStart(0, 0);
    //plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    //plotGradient.setColorAt(1, QColor(50, 50, 50));
   ui->widget->setBackground(plotGradient);

   //设置坐标颜色/坐标名称颜色
    ui->widget->xAxis->setLabelColor(Qt::white);//文字颜色
    ui->widget->yAxis->setLabelColor(Qt::white);
    ui->widget->xAxis->setTickLabelColor(Qt::white);//坐标轴数字颜色
    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->setBasePen(QPen(Qt::white, 1));//坐标轴颜色及宽度
    ui->widget->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));//主刻度
    ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));//副刻度
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));


    //设置属性可缩放，移动等
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                         QCP::iSelectLegend | QCP::iSelectPlottables);
    CustomPlot->addGraph();//添加一条曲线
    CustomPlot->graph(0)->setPen(QPen(Qt::green)); //0是曲线序号，添加的第一条是0，设置曲线颜色
    CustomPlot->graph(0)->setData(temp,temp1); //输出各点的图像，x和y都是QVector类

    CustomPlot->xAxis->setLabel("x");//x轴的文字
    CustomPlot->yAxis->setLabel("y");//y轴的文字

    CustomPlot->xAxis->setRange(0,100);//x轴范围
    CustomPlot->yAxis->setRange(-100,200);//y轴范围
    CustomPlot->replot();//重绘
    CustomPlot->addGraph();//添加第二条曲线
    CustomPlot->graph(1)->setPen(QPen(Qt::yellow)); //1是曲线序号，添加的第二条是1，设置曲线颜色
    CustomPlot->graph(1)->setData(temp,temp2);
}

