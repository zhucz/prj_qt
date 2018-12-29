#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    timerId = this->startTimer(1000);//100ms
    timerId2 = this->startTimer(500);//100ms


    connect(ui->pushButton, &MyButton::clicked,
            []()
            {
                qDebug() << "按钮被按下";
            }
            );

    //安装过滤器
    ui->label_2->installEventFilter(this);
    ui->label_2->setMouseTracking(true);

    /*
     * 注意：
     * 事件过滤器和被安装过滤器的组件必须在同一线程，否则，过滤器将不起作用
     * 另外，如果安装过滤器之后，这两个组件到了不同的线程，那么只有等到二者重新回到同一线程的时候过滤器才会有效。
    */


}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << (char)event->key();
    if(event->key() == Qt::Key_A){
        qDebug() << "Qt::Key_A";
    }
}


void MyWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == this->timerId){
        static int sec = 0;
        sec++;
        ui->label->setText(QString("<center><h1>tine out %1</h1> </center>").arg(sec));

        if(sec == 5){
            //停止定时器
            this->killTimer(this->timerId);
        }
    }else if(event->timerId() == this->timerId2){
        static int sec = 0;
        sec++;
        ui->label_2->setText(QString("<center><h1>tine out %1</h1> </center>").arg(sec));

    }



}


void MyWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "++++++++++";

}


void MyWidget::closeEvent(QCloseEvent *event)
{

    int ret = QMessageBox::question(this, "question","是否需要关闭");
    if(ret == QMessageBox::Yes){
        //关闭窗口
        //处理关闭窗口事件，接收事件，事件就不会往下传递
        event->accept();

    }else{
        //不关闭窗口
        //忽略事件，事件继续给父组件传递
        event->ignore();
    }

}

/*通常不要修改这个函数*/
bool MyWidget::event(QEvent *event)
{
    //事件分发
//    switch(event->type()){
//        case QEvent::Close:
//            closeEvent(event);
//            break;
//        case QEvent::MouseMove:
//            mouseMoveEvent(event);
//            break;
//    }



    if(event->type() == QEvent::Timer){
        //干掉定时器
        //如果返回true，事件停止传播
        //QTimerEvent *e 和QEvent *e 需要类型转换
        QTimerEvent *env = static_cast<QTimerEvent *>(event);
        timerEvent(env);



        return true;
    }
    else if(event->type() == QKeyEvent::KeyPress){
        //类型转换
        QKeyEvent *env = static_cast<QKeyEvent *>(event);
        if(env->key() == Qt::Key_B){
            return QWidget::event(event);
        }
        return true;

    }
    else{//只是干掉定时器，其他继续
        return QWidget::event(event);
    }
}


bool MyWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_2){
        //类型转换
        QMouseEvent *env = static_cast<QMouseEvent *>(event);

        //判断事件
        if(event->type() == QEvent::MouseMove){
            ui->label_2->setText(QString("Mouse move:(%1,%2)").arg(env->x()).arg(env->y()));
            return true;
        }else if(event->type() == QEvent::MouseButtonRelease){
            ui->label_2->setText(QString("Mouse release:(%1,%2)").arg(env->x()).arg(env->y()));
            return true;
        }
        else{
           return QWidget::eventFilter(watched, event);
        }

    }else{
        return QWidget::eventFilter(watched, event);
    }

//    //其他空间的过滤方式
//    if(watched == ui->pushButton){

//    }
}


MyWidget::~MyWidget()
{
    delete ui;
}
