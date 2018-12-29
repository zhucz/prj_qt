#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include "thread.h"
#include <QFont>
#include "cmd_type.h"
//sleep
#include <QApplication>
#include <QTimer>
#include <QObject>

#include <QMap>
#include <QColor>
#include <QTextEdit>
#include <Qt>



#include "crc8.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /*2017-06-07 自动获取系统中可用的串口*/
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort myserial;
        myserial.setPort(info);
        if(myserial.open(QIODevice::ReadWrite)){
            ui->comboBox->addItem(myserial.portName());
            myserial.close();
        }
    }

    ui->comboBox->setCurrentIndex(1);
    /*---------  end  --------*/


     serial = new QSerialPort();

     ui->textEdit_14->hide();
     ui->textEdit_15->hide();
     ui->textEdit_16->hide();
     ui->textEdit_17->hide();
     ui->textEdit_18->hide();

     send_time_count = 145;
     delay_cnt = 200;
     cunt_hub_num = 1;

     timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()),this,SLOT(my_uart_timer_update()));
     //timer->start(1000);
     first_read_tary_v = 0;


     QDateTime time = QDateTime::currentDateTime();
     QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
     ui->label->setText(str);

     ui->progressBar->setValue(0);
}

Widget::~Widget()
{
    delete ui;
}


/*定时器超时处理函数*/
void Widget::my_uart_timer_update()
{
//    unsigned char tray_20[8]    = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
//    unsigned char jkb_hub_20[7] = {0x7e,0x00,0x05,0x20,0x01,0x71,0x5a};

    switch(cmd_type){
        case LED_LIGHT_BUTTON:
             QMessageBox::information(NULL,"LED","亮灯失败",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
             break;
        case LED_OFF_BUTTON:
             QMessageBox::information(NULL,"LED","灭灯失败",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
             break;
        case READ_TRAY_VERSION:
             ui->textEdit->clear();
             QMessageBox::information(NULL,"TRAYVERSION","读取盘版本号失败",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
             break;
        case READ_TRAY_PORT_INFO:

            for(int i = 0 ;i < 12; i++){
                set_color_for_textEdit(i+2,GRAP);
            }
            QMessageBox::information(NULL,"PORTINFO","读取EID失败",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            break;
        case HUB_YI_JIAN_READ_VERSION:
            ui->textEdit_49->clear();
            ui->textEdit_19->clear();
            ui->textEdit_20->clear();
            ui->textEdit_21->clear();
            ui->textEdit_22->clear();
            ui->textEdit_23->clear();
            ui->textEdit_24->clear();

            set_color_for_textEdit(37,GRAP);
            set_color_for_textEdit(40,GRAP);
            set_color_for_textEdit(36,GRAP);
            set_color_for_textEdit(25,GRAP);
            set_color_for_textEdit(39,GRAP);
            set_color_for_textEdit(38,GRAP);
            set_color_for_textEdit(35,GRAP);
            QMessageBox::information(NULL,"VERSION","一键读取版本失败",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            break;
    }
    timer->stop();
}

/*毫秒延时函数*/
void sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

/*
 * 打开串口
 */
void Widget::on_pushButton_3_clicked()
{
    if(ui->comboBox->isEnabled()){

            serial->setPortName(ui->comboBox->currentText());
            serial->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
            serial->setDataBits(QSerialPort::Data8);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->open(QIODevice::ReadWrite);
            if(serial->isOpen() == 0){
                QMessageBox::information(NULL,"Title","串口被占用",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                return;
            }else{

            }

        ui->pushButton_3->setText("关闭串口");  //按下“OpenPort”后，按键显示为“ClosePort”
        ui->comboBox->setDisabled(true);

        connect(serial,SIGNAL(readyRead()),this,SLOT(my_readuart()));
    }else{
        ui->pushButton_3->setText("打开串口");
        ui->comboBox->setEnabled(true);
        serial->close();

    }
}

/*设置textEdit 的背景颜色*/
#if 1
void Widget::set_color_for_textEdit(int num,int color)
{
    QPalette palette;
    switch(num){
        case 1:
             palette = ui->textEdit->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit->setPalette(palette);
            }else{

            }
            break;

        case 2:
            palette = ui->textEdit_2->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_2->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_2->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_2->setPalette(palette);
            }else{

            }
            break;
        case 3:
            palette = ui->textEdit_3->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_3->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_3->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_3->setPalette(palette);
            }else{

            }
            break;

        case 4:
            palette = ui->textEdit_4->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_4->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_4->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_4->setPalette(palette);
            }else{

            }
            break;

        case 5:
            palette = ui->textEdit_5->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_5->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_5->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_5->setPalette(palette);
            }else{

            }
            break;

        case 6:
            palette = ui->textEdit_6->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_6->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_6->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_6->setPalette(palette);
            }else{

            }
            break;

        case 7:
            palette = ui->textEdit_7->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_7->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_7->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_7->setPalette(palette);
            }else{

            }
            break;

        case 8:
            palette = ui->textEdit_8->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_8->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_8->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_8->setPalette(palette);
            }else{

            }
            break;

        case 9:
            palette = ui->textEdit_9->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_9->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_9->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_9->setPalette(palette);
            }else{

            }
            break;

    case 10:
        palette = ui->textEdit_10->palette();
        if(color == 0x01){//红色
            palette.setColor(QPalette::Base,QColor(255,0,0));
            ui->textEdit_10->setPalette(palette);
        }else if(color == 0x02){//绿色
            palette.setColor(QPalette::Base,QColor(0,250,154));
            ui->textEdit_10->setPalette(palette);
        }else if(color == 0x03){//灰色
            palette.setColor(QPalette::Base,QColor(139,134,130));
            ui->textEdit_10->setPalette(palette);
        }else{

        }
        break;

    case 11:
        palette = ui->textEdit_11->palette();
        if(color == 0x01){//红色
            palette.setColor(QPalette::Base,QColor(255,0,0));
            ui->textEdit_11->setPalette(palette);
        }else if(color == 0x02){//绿色
            palette.setColor(QPalette::Base,QColor(0,250,154));
            ui->textEdit_11->setPalette(palette);
        }else if(color == 0x03){//灰色
            palette.setColor(QPalette::Base,QColor(139,134,130));
            ui->textEdit_11->setPalette(palette);
        }else{

        }
        break;

        case 12:
            palette = ui->textEdit_12->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_12->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_12->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_12->setPalette(palette);
            }else{

            }
            break;

        case 13:
            palette = ui->textEdit_13->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_13->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_13->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_13->setPalette(palette);
            }else{

            }
            break;



        case 14:
            palette = ui->textEdit_14->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_14->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_14->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_14->setPalette(palette);
            }else{

            }
            break;

        case 15:
            palette = ui->textEdit_15->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_15->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_15->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_15->setPalette(palette);
            }else{

            }
            break;

        case 16:
            palette = ui->textEdit_16->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_16->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_16->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_16->setPalette(palette);
            }else{

            }
            break;

        case 17:
            palette = ui->textEdit_17->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_17->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_17->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_17->setPalette(palette);
            }else{

            }
            break;

        case 18:
            palette = ui->textEdit_18->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_18->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_18->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_18->setPalette(palette);
            }else{

            }
            break;

        case 19:
            palette = ui->textEdit_19->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_19->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_19->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_19->setPalette(palette);
            }else{

            }
            break;

        case 20:
            palette = ui->textEdit_20->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_20->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_20->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_20->setPalette(palette);
            }else{

            }
            break;

        case 21:
            palette = ui->textEdit_21->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_21->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_21->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_21->setPalette(palette);
            }else{

            }
            break;

        case 22:
            palette = ui->textEdit_22->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_22->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_22->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_22->setPalette(palette);
            }else{

            }
            break;

        case 23:
            palette = ui->textEdit_23->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_23->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_23->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_23->setPalette(palette);
            }else{

            }
            break;

        case 24:
            palette = ui->textEdit_24->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_24->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_24->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_24->setPalette(palette);
            }else{

            }
            break;

        case 25:
            palette = ui->textEdit_25->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_25->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_25->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_25->setPalette(palette);
            }else{

            }
            break;

        case 26:
            palette = ui->textEdit_26->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_26->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_26->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_26->setPalette(palette);
            }else{

            }
            break;



            case 27:
                palette = ui->textEdit_27->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_27->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_27->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_27->setPalette(palette);
                }else{

                }
                break;

            case 28:
                palette = ui->textEdit_28->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_28->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_28->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_28->setPalette(palette);
                }else{

                }
                break;

        case 29:
            palette = ui->textEdit_29->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_29->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_29->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_29->setPalette(palette);
            }else{

            }
            break;

        case 30:
            palette = ui->textEdit_30->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_30->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_30->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_30->setPalette(palette);
            }else{

            }
            break;

        case 31:
            palette = ui->textEdit_31->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_31->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_31->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_31->setPalette(palette);
            }else{

            }
            break;

        case 32:
            palette = ui->textEdit_32->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_32->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_32->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_32->setPalette(palette);
            }else{

            }
            break;

        case 33:
            palette = ui->textEdit_33->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_33->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_33->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_33->setPalette(palette);
            }else{

            }
            break;

        case 34:
            palette = ui->textEdit_34->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_34->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_34->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_34->setPalette(palette);
            }else{

            }
            break;

        case 35:
            palette = ui->textEdit_35->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_35->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_35->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_35->setPalette(palette);
            }else{

            }
            break;

        case 36:
            palette = ui->textEdit_36->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_36->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_36->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_36->setPalette(palette);
            }else{

            }
            break;

        case 37:
            palette = ui->textEdit_37->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_37->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_37->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_37->setPalette(palette);
            }else{

            }
            break;

        case 38:
            palette = ui->textEdit_38->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_38->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_38->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_38->setPalette(palette);
            }else{

            }
            break;

        case 39:
            palette = ui->textEdit_39->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_39->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_39->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_39->setPalette(palette);
            }else{

            }
            break;


            case 40:
                palette = ui->textEdit_40->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_40->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_40->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_40->setPalette(palette);
                }else{

                }
                break;

            case 41:
                palette = ui->textEdit_41->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_41->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_41->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_41->setPalette(palette);
                }else{

                }
                break;

            case 42:
                palette = ui->textEdit_42->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_42->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_42->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_42->setPalette(palette);
                }else{

                }
                break;

            case 43:
                palette = ui->textEdit_43->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_43->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_43->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_43->setPalette(palette);
                }else{

                }
                break;

            case 44:
                palette = ui->textEdit_44->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_44->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_44->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_44->setPalette(palette);
                }else{

                }
                break;

            case 45:
                palette = ui->textEdit_45->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_45->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_45->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_45->setPalette(palette);
                }else{

                }
                break;

            case 46:
                palette = ui->textEdit_46->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_46->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_46->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_46->setPalette(palette);
                }else{

                }
                break;

            case 47:
                palette = ui->textEdit_47->palette();
                if(color == 0x01){//红色
                    palette.setColor(QPalette::Base,QColor(255,0,0));
                    ui->textEdit_47->setPalette(palette);
                }else if(color == 0x02){//绿色
                    palette.setColor(QPalette::Base,QColor(0,250,154));
                    ui->textEdit_47->setPalette(palette);
                }else if(color == 0x03){//灰色
                    palette.setColor(QPalette::Base,QColor(139,134,130));
                    ui->textEdit_47->setPalette(palette);
                }else{

                }
                break;

        case 48:
            palette = ui->textEdit_48->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_48->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_48->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_48->setPalette(palette);
            }else{

            }
            break;
        case 49:
            palette = ui->textEdit_48->palette();
            if(color == 0x01){//红色
                palette.setColor(QPalette::Base,QColor(255,0,0));
                ui->textEdit_48->setPalette(palette);
            }else if(color == 0x02){//绿色
                palette.setColor(QPalette::Base,QColor(0,250,154));
                ui->textEdit_48->setPalette(palette);
            }else if(color == 0x03){//灰色
                palette.setColor(QPalette::Base,QColor(139,134,130));
                ui->textEdit_48->setPalette(palette);
            }else if(color == 0x04){//透明
                palette.setColor(QPalette::Base,QColor(0x00,0xff,0x00,0x00));
                ui->textEdit_48->setPalette(palette);
            }else{

            }
            break;
        default:
            break;

    }
}
#endif



/*
 * LED 亮灯测试
 */
void Widget::product_test_led_on(QByteArray src)
{
    unsigned char led_light_20[8] = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
    unsigned char led_light_10[9] = {0x7e,0x00,0x07,0x10,0x01,0x01,0xff,0x48,0x5a};
    unsigned char led_light_a6[7] = {0x7e,0x00,0x05,0xa6,0x01,0x08,0x5a};


    switch ((unsigned char )src.data()[3]) {
        case 0x20:
            serial->write((char *)led_light_10,9);
            ui->progressBar->setValue(40);
            break;
        case 0x10:
            timer->stop();
            serial->write((char *)led_light_a6,7);
            ui->progressBar->setValue(100);
            QMessageBox::information(NULL,"LED","亮灯成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            break;
        case 0xa6:
            ui->progressBar->setValue(60);
            sleep(10);
            serial->write((char *)led_light_20,8);
            break;
        default:

            led_light_a6[5] = calc_crc8->mycrc8(led_light_a6,5);
            serial->write((char *)led_light_a6,9);
            serial->waitForBytesWritten(send_time_count);
            sleep(delay_cnt);
            serial->write((char *)led_light_10,9);
            break;
    }
    serial->waitForBytesWritten(send_time_count);
}

/*
 * LED 灭灯
 */
void Widget::product_test_led_off(QByteArray src)
{
    unsigned char led_off_20[8] = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
    unsigned char led_off_10[9] = {0x7e,0x00,0x07,0x10,0x01,0x01,0xfe,0x79,0x5a};
    unsigned char led_off_a6[7] = {0x7e,0x00,0x05,0xa6,0x01,0x08,0x5a};


    switch ((unsigned char )src.data()[3]) {
        case 0x20:
            serial->write((char *)led_off_10,9);
            ui->progressBar->setValue(40);
            break;
        case 0x10:
            timer->stop();
            serial->write((char *)led_off_a6,7);
            ui->progressBar->setValue(100);
            QMessageBox::information(NULL,"LED","灭灯成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            break;
        case 0xa6:
            sleep(10);
            serial->write((char *)led_off_20,8);
            ui->progressBar->setValue(60);
            break;
        default:
            led_off_a6[5] = calc_crc8->mycrc8(led_off_a6,7);
            serial->write((char *)led_off_a6,7);
            sleep(delay_cnt);
            serial->write((char *)led_off_10,9);
            break;
    }
    serial->waitForBytesWritten(send_time_count);
}


/*
 * 读取单元板软硬件版本号
 */
void Widget::read_one_tray_version(QByteArray src)
{
    unsigned char t_version_20[8] = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
    unsigned char t_version_05[8] = {0x7e,0x00,0x06,0x05,0x01,0x01,0x72,0x5a};
    unsigned char t_version_a6[7] = {0x7e,0x00,0x05,0xa6,0x01,0x08,0x5a};


    QByteArray version;
    QByteArray data_timer;
    QByteArray type;
    QByteArray frame;
    QByteArray tray;

    version.resize(2);
    data_timer.resize(8);
    type.resize(1);
    frame.resize(1);
    tray.resize(1);

    switch ((unsigned char )src.data()[3]) {
        case 0x20:
            serial->write((char *)t_version_05,8);
            ui->progressBar->setValue(40);
            break;
        case 0x05:
            timer->stop();
            serial->write((char *)t_version_a6,7);

            version = src.mid(7,2);
            data_timer = src.mid(9,8);
            type = src.mid(17,1);
            frame = src.mid(18,1);
            tray = src.mid(19,1);

            ui->textEdit->clear();
            ui->textEdit->insertPlainText("版本：");
            ui->textEdit->insertPlainText(version.toHex());

            ui->textEdit->insertPlainText(" ");
            ui->textEdit->insertPlainText("期日：");
            ui->textEdit->insertPlainText(data_timer.toHex());

            ui->textEdit->insertPlainText(" ");
            ui->textEdit->insertPlainText("类型：");
            ui->textEdit->insertPlainText(type.toHex());

            ui->textEdit->insertPlainText(" ");
            ui->textEdit->insertPlainText("框号：");
            ui->textEdit->insertPlainText(frame.toHex());

            ui->textEdit->insertPlainText(" ");
            ui->textEdit->insertPlainText("盘号：");
            ui->textEdit->insertPlainText(tray.toHex());

            if(src.data()[4] == 0x11){
                ui->textEdit_14->show();
                ui->textEdit_15->show();
                ui->textEdit_16->show();
                ui->textEdit_17->show();
                ui->textEdit_18->show();
            }

            first_read_tary_v = 1;
            ui->progressBar->setValue(100);
            QMessageBox::information(NULL,"TRAYVERSION","读取盘版本号成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);

            break;
        case 0xa6:
            sleep(10);
            serial->write((char *)t_version_20,8);
            ui->progressBar->setValue(60);
            break;
        default:
            t_version_a6[5] = calc_crc8->mycrc8(t_version_a6,7);
            serial->write((char *)t_version_a6,7);
            sleep(delay_cnt);
            serial->write((char *)t_version_05,8);
            break;
    }
    serial->waitForBytesWritten(send_time_count);
}


/*
 * 读取单元板端口的EID信息
 */
//数据处理显示
void Widget::disp_eid_port_info_colo(QByteArray src)
{
    QByteArray eid_0x00;
    QByteArray eid_0xff;
    QByteArray temp_eid;

    eid_0x00.resize(32);
    eid_0xff.resize(32);
    temp_eid.reserve(32);

    eid_0x00.clear();
    eid_0xff.clear();
    temp_eid.clear();

    eid_0x00.fill(0x00,32);
    eid_0xff.fill(0xff,32);


    for(int i = 0 ;i < 12; i++){
        if(!qstrncmp(&src.data()[8+(i*35)],&eid_0xff.data()[0],32)){
            set_color_for_textEdit(i+2,GRAP);
        }else if (!qstrncmp(&src.data()[8+(i*35)],&eid_0x00.data()[0],32)){
            set_color_for_textEdit(i+2,READ);
        }else{
            set_color_for_textEdit(i+2,GREEN);
        }
    }
    QMessageBox::information(NULL,"PORTINFO","读取EID成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);

}

/*读取盘EID信息数据发送*/
void Widget::read_one_tray_port_info(QByteArray src)
{
    unsigned char t_portinfo_20[8] =   {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
    unsigned char t_portinfo_0d01[8] = {0x7e,0x00,0x06,0x0d,0x11,0x01,0x20,0x5a};
    unsigned char t_portinfo_a6[7] =   {0x7e,0x00,0x05,0xa6,0x01,0x08,0x5a};


    switch ((unsigned char )src.data()[3]) {
        case 0x20:
            t_portinfo_0d01[6] = calc_crc8->mycrc8(t_portinfo_0d01,6);
            serial->write((char *)t_portinfo_0d01,8);
            ui->progressBar->setValue(40);
            break;
        case 0x0d:
            timer->stop();
            serial->write((char *)t_portinfo_a6,7);
            disp_eid_port_info_colo(src);
            ui->progressBar->setValue(100);
            break;
        case 0xa6:
            sleep(100);
            serial->write((char *)t_portinfo_20,8);
            ui->progressBar->setValue(60);
            break;
        default:
            serial->write((char *)t_portinfo_a6,7);
            sleep(delay_cnt);
            serial->write((char *)t_portinfo_0d01,8);
            break;
    }
    serial->waitForBytesWritten(send_time_count);
}



/*HUB 一键读取版本号*/
//数据处理
void Widget::disp_yi_jian_hub_read_version_info(QByteArray src)
{
    QByteArray version;
    QByteArray data_timer;
    QByteArray type;
    QByteArray frame;
    QByteArray tray;

    QTextCursor start;

    version.resize(2);
    data_timer.resize(8);
    type.resize(1);
    frame.resize(1);
    tray.resize(1);


    ui->textEdit_49->clear();
    ui->textEdit_19->clear();
    ui->textEdit_20->clear();
    ui->textEdit_21->clear();
    ui->textEdit_22->clear();
    ui->textEdit_23->clear();
    ui->textEdit_24->clear();
    sleep(1000);
/*HUB*/
    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);


    ui->textEdit_49->insertPlainText("版本：");
    ui->textEdit_49->insertPlainText(version.toHex());

    ui->textEdit_49->insertPlainText(" ");
    ui->textEdit_49->insertPlainText("期日：");
    ui->textEdit_49->insertPlainText(data_timer.toHex());

    ui->textEdit_49->insertPlainText(" ");
    ui->textEdit_49->insertPlainText("类型：");
    ui->textEdit_49->insertPlainText(type.toHex());

    ui->textEdit_49->insertPlainText(" ");
    ui->textEdit_49->insertPlainText("框号：");
    ui->textEdit_49->insertPlainText(frame.toHex());

    ui->textEdit_49->insertPlainText(" ");
    ui->textEdit_49->insertPlainText("盘号：");
    ui->textEdit_49->insertPlainText(tray.toHex());
    if(frame.data()[0] == 0x00){
        set_color_for_textEdit(37,READ);
    }else{
        set_color_for_textEdit(37,GREEN);
    }
    //ui->textEdit_49->moveCursor(start.Start);


/*一号盘*/
    version = src.mid(55,2);
    data_timer = src.mid(57,8);
    type = src.mid(65,1);
    frame = src.mid(66,1);
    tray = src.mid(67,1);


    ui->textEdit_19->insertPlainText("版本：");
    ui->textEdit_19->insertPlainText(version.toHex());

    ui->textEdit_19->insertPlainText(" ");
    ui->textEdit_19->insertPlainText("期日：");
    ui->textEdit_19->insertPlainText(data_timer.toHex());

    ui->textEdit_19->insertPlainText(" ");
    ui->textEdit_19->insertPlainText("类型：");
    ui->textEdit_19->insertPlainText(type.toHex());

    ui->textEdit_19->insertPlainText(" ");
    ui->textEdit_19->insertPlainText("框号：");
    ui->textEdit_19->insertPlainText(frame.toHex());

    ui->textEdit_19->insertPlainText(" ");
    ui->textEdit_19->insertPlainText("盘号：");
    ui->textEdit_19->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(40,READ);
    }else{
        set_color_for_textEdit(40,GREEN);
    }
    //ui->textEdit_19->moveCursor(start.Start);

    /*二号盘*/
    version = src.mid(7+48+48,2);
    data_timer = src.mid(9+48+48,8);
    type = src.mid(17+48+48,1);
    frame = src.mid(18+48+48,1);
    tray = src.mid(19+48+48,1);

    ui->textEdit_20->insertPlainText("版本：");
    ui->textEdit_20->insertPlainText(version.toHex());

    ui->textEdit_20->insertPlainText(" ");
    ui->textEdit_20->insertPlainText("期日：");
    ui->textEdit_20->insertPlainText(data_timer.toHex());

    ui->textEdit_20->insertPlainText(" ");
    ui->textEdit_20->insertPlainText("类型：");
    ui->textEdit_20->insertPlainText(type.toHex());

    ui->textEdit_20->insertPlainText(" ");
    ui->textEdit_20->insertPlainText("框号：");
    ui->textEdit_20->insertPlainText(frame.toHex());

    ui->textEdit_20->insertPlainText(" ");
    ui->textEdit_20->insertPlainText("盘号：");
    ui->textEdit_20->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(36,READ);
    }else{
        set_color_for_textEdit(36,GREEN);
    }
    //ui->textEdit_20->moveCursor(start.Start);

    /*三号盘*/
    version = src.mid(7+48+48+48,2);
    data_timer = src.mid(9+48+48+48,8);
    type = src.mid(17+48+48+48,1);
    frame = src.mid(18+48+48+48,1);
    tray = src.mid(19+48+48+48,1);

    ui->textEdit_21->insertPlainText("版本：");
    ui->textEdit_21->insertPlainText(version.toHex());

    ui->textEdit_21->insertPlainText(" ");
    ui->textEdit_21->insertPlainText("期日：");
    ui->textEdit_21->insertPlainText(data_timer.toHex());

    ui->textEdit_21->insertPlainText(" ");
    ui->textEdit_21->insertPlainText("类型：");
    ui->textEdit_21->insertPlainText(type.toHex());

    ui->textEdit_21->insertPlainText(" ");
    ui->textEdit_21->insertPlainText("框号：");
    ui->textEdit_21->insertPlainText(frame.toHex());

    ui->textEdit_21->insertPlainText(" ");
    ui->textEdit_21->insertPlainText("盘号：");
    ui->textEdit_21->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(25,READ);
    }else{
        set_color_for_textEdit(25,GREEN);
    }
   // ui->textEdit_21->moveCursor(start.Start);

    /*四号盘*/
    version = src.mid(7+48+48+48+48,2);
    data_timer = src.mid(9+48,8);
    type = src.mid(17+48+48+48+48+48,1);
    frame = src.mid(18+48+48+48+48,1);
    tray = src.mid(19+48+48+48+48,1);

    ui->textEdit_22->insertPlainText("版本：");
    ui->textEdit_22->insertPlainText(version.toHex());

    ui->textEdit_22->insertPlainText(" ");
    ui->textEdit_22->insertPlainText("期日：");
    ui->textEdit_22->insertPlainText(data_timer.toHex());

    ui->textEdit_22->insertPlainText(" ");
    ui->textEdit_22->insertPlainText("类型：");
    ui->textEdit_22->insertPlainText(type.toHex());

    ui->textEdit_22->insertPlainText(" ");
    ui->textEdit_22->insertPlainText("框号：");
    ui->textEdit_22->insertPlainText(frame.toHex());

    ui->textEdit_22->insertPlainText(" ");
    ui->textEdit_22->insertPlainText("盘号：");
    ui->textEdit_22->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(39,READ);
    }else{
        set_color_for_textEdit(39,GREEN);
    }

    //ui->textEdit_22->moveCursor(start.Start);

    /*五号盘*/
    version = src.mid(7+48+48+48+48+48,2);
    data_timer = src.mid(9+48+48+48+48+48,8);
    type = src.mid(17+48+48+48+48+48,1);
    frame = src.mid(18+48+48+48+48+48,1);
    tray = src.mid(19+48+48+48+48+48,1);

    ui->textEdit_23->insertPlainText("版本：");
    ui->textEdit_23->insertPlainText(version.toHex());

    ui->textEdit_23->insertPlainText(" ");
    ui->textEdit_23->insertPlainText("期日：");
    ui->textEdit_23->insertPlainText(data_timer.toHex());

    ui->textEdit_23->insertPlainText(" ");
    ui->textEdit_23->insertPlainText("类型：");
    ui->textEdit_23->insertPlainText(type.toHex());

    ui->textEdit_23->insertPlainText(" ");
    ui->textEdit_23->insertPlainText("框号：");
    ui->textEdit_23->insertPlainText(frame.toHex());

    ui->textEdit_23->insertPlainText(" ");
    ui->textEdit_23->insertPlainText("盘号：");
    ui->textEdit_23->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(38,READ);
    }else{
        set_color_for_textEdit(38,GREEN);
    }
    //ui->textEdit_23->moveCursor(start.Start);

    /*六号盘*/
    version = src.mid(7+48+48+48+48+48+48,2);
    data_timer = src.mid(9+48+48+48+48+48+48,8);
    type = src.mid(17+48+48+48+48+48+48,1);
    frame = src.mid(18+48+48+48+48+48+48,1);
    tray = src.mid(19+48+48+48+48+48+48,1);

    ui->textEdit_24->insertPlainText("版本：");
    ui->textEdit_24->insertPlainText(version.toHex());

    ui->textEdit_24->insertPlainText(" ");
    ui->textEdit_24->insertPlainText("期日：");
    ui->textEdit_24->insertPlainText(data_timer.toHex());

    ui->textEdit_24->insertPlainText(" ");
    ui->textEdit_24->insertPlainText("类型：");
    ui->textEdit_24->insertPlainText(type.toHex());

    ui->textEdit_24->insertPlainText(" ");
    ui->textEdit_24->insertPlainText("框号：");
    ui->textEdit_24->insertPlainText(frame.toHex());

    ui->textEdit_24->insertPlainText(" ");
    ui->textEdit_24->insertPlainText("盘号：");
    ui->textEdit_24->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(35,READ);
    }else{
        set_color_for_textEdit(35,GREEN);
    }
    //ui->textEdit_24->moveCursor(start.Start);

}
//数据发送
void Widget::hub_yi_jian_read_version_info(QByteArray src)
{
    unsigned char t_hub_v_a6_kaiji[9] =   {0x7e,0x00,0x07,0xa6,0x10,0x02,0x01,0xAA,0x5a};
    unsigned char t_hub_v_20[7] =         {0x7e,0x00,0x05,0x20,0x01,0x71,0x5a};
    unsigned char t_hub_v_05[8] =         {0x7e,0x00,0x06,0x05,0x01,0xFF,0xEF,0x5a};
    unsigned char t_hub_v_a6_v[9] =       {0x7e,0x00,0x07,0xa6,0xAA,0x01,0x01,0x51,0x5a};


    switch ((unsigned char )src.data()[3]) {
        case 0x10:
            serial->write((char *)t_hub_v_a6_kaiji,9);
            serial->waitForBytesWritten(send_time_count);
            sleep(delay_cnt);
            serial->write((char *)t_hub_v_20,7);
            ui->progressBar->setValue(20);
            break;
        case 0x20:
            serial->write((char *)t_hub_v_05,8);
            sleep(delay_cnt);
            ui->progressBar->setValue(40);
            break;
        case 0xaa:
            timer->stop();
            serial->write((char *)t_hub_v_a6_v,9);
            serial->waitForBytesWritten(send_time_count);
            disp_yi_jian_hub_read_version_info(src);
            //timer->stop();
            ui->progressBar->setValue(100);
            QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);

            break;
        case 0xa6:
            sleep(2000);
            serial->write((char *)t_hub_v_20,7);
            ui->progressBar->setValue(60);
            break;
        default:
            serial->write((char *)t_hub_v_a6_v,9);
            sleep(delay_cnt);
            serial->write((char *)t_hub_v_05,8);
            break;
    }
    serial->waitForBytesWritten(send_time_count);
}


/*JK 一键读取版本号*/
//数据处理
void Widget::disp_yi_jian_jk_read_version_info(QByteArray src)
{
    QByteArray version;
    QByteArray data_timer;
    QByteArray type;
    QByteArray frame;
    QByteArray tray;

    QTextCursor start;

    version.resize(2);
    data_timer.resize(8);
    type.resize(1);
    frame.resize(1);
    tray.resize(1);










/*一号HUB*/
    if(cunt_hub_num == 1){
    ui->textEdit_28->clear();
    sleep(1000);

    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);


    ui->textEdit_28->insertPlainText("版本：");
    ui->textEdit_28->insertPlainText(version.toHex());

    ui->textEdit_28->insertPlainText(" ");
    ui->textEdit_28->insertPlainText("期日：");
    ui->textEdit_28->insertPlainText(data_timer.toHex());

    ui->textEdit_28->insertPlainText(" ");
    ui->textEdit_28->insertPlainText("类型：");
    ui->textEdit_28->insertPlainText(type.toHex());

    ui->textEdit_28->insertPlainText(" ");
    ui->textEdit_28->insertPlainText("框号：");
    ui->textEdit_28->insertPlainText(frame.toHex());

    ui->textEdit_28->insertPlainText(" ");
    ui->textEdit_28->insertPlainText("盘号：");
    ui->textEdit_28->insertPlainText(tray.toHex());
    if(frame.data()[0] == 0x00){
        set_color_for_textEdit(37,READ);
    }else{
        set_color_for_textEdit(37,GREEN);
    }
    //ui->textEdit_49->moveCursor(start.Start);
}

    /*二号HUB*/
        if(cunt_hub_num == 2){
        ui->textEdit_27->clear();
            sleep(1000);

    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);


    ui->textEdit_27->insertPlainText("版本：");
    ui->textEdit_27->insertPlainText(version.toHex());

    ui->textEdit_27->insertPlainText(" ");
    ui->textEdit_27->insertPlainText("期日：");
    ui->textEdit_27->insertPlainText(data_timer.toHex());

    ui->textEdit_27->insertPlainText(" ");
    ui->textEdit_27->insertPlainText("类型：");
    ui->textEdit_27->insertPlainText(type.toHex());

    ui->textEdit_27->insertPlainText(" ");
    ui->textEdit_27->insertPlainText("框号：");
    ui->textEdit_27->insertPlainText(frame.toHex());

    ui->textEdit_27->insertPlainText(" ");
    ui->textEdit_27->insertPlainText("盘号：");
    ui->textEdit_27->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(40,READ);
    }else{
        set_color_for_textEdit(40,GREEN);
    }
    //ui->textEdit_19->moveCursor(start.Start);
}
    /*三号HUB*/
            if(cunt_hub_num == 3){
        ui->textEdit_26->clear();
            sleep(1000);


    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    ui->textEdit_26->insertPlainText("版本：");
    ui->textEdit_26->insertPlainText(version.toHex());

    ui->textEdit_26->insertPlainText(" ");
    ui->textEdit_26->insertPlainText("期日：");
    ui->textEdit_26->insertPlainText(data_timer.toHex());

    ui->textEdit_26->insertPlainText(" ");
    ui->textEdit_26->insertPlainText("类型：");
    ui->textEdit_26->insertPlainText(type.toHex());

    ui->textEdit_26->insertPlainText(" ");
    ui->textEdit_26->insertPlainText("框号：");
    ui->textEdit_26->insertPlainText(frame.toHex());

    ui->textEdit_26->insertPlainText(" ");
    ui->textEdit_26->insertPlainText("盘号：");
    ui->textEdit_26->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(36,READ);
    }else{
        set_color_for_textEdit(36,GREEN);
    }
    //ui->textEdit_20->moveCursor(start.Start);
}


    /*四号HUB*/
                if(cunt_hub_num == 4){
        ui->textEdit_30->clear();
            sleep(1000);


    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    ui->textEdit_30->insertPlainText("版本：");
    ui->textEdit_30->insertPlainText(version.toHex());

    ui->textEdit_30->insertPlainText(" ");
    ui->textEdit_30->insertPlainText("期日：");
    ui->textEdit_30->insertPlainText(data_timer.toHex());

    ui->textEdit_30->insertPlainText(" ");
    ui->textEdit_30->insertPlainText("类型：");
    ui->textEdit_30->insertPlainText(type.toHex());

    ui->textEdit_30->insertPlainText(" ");
    ui->textEdit_30->insertPlainText("框号：");
    ui->textEdit_30->insertPlainText(frame.toHex());

    ui->textEdit_30->insertPlainText(" ");
    ui->textEdit_30->insertPlainText("盘号：");
    ui->textEdit_30->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(25,READ);
    }else{
        set_color_for_textEdit(25,GREEN);
    }
   // ui->textEdit_21->moveCursor(start.Start);
}


    /*五号HUB*/
    if(cunt_hub_num == 5){
        ui->textEdit_31->clear();
            sleep(1000);


    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    ui->textEdit_31->insertPlainText("版本：");
    ui->textEdit_31->insertPlainText(version.toHex());

    ui->textEdit_31->insertPlainText(" ");
    ui->textEdit_31->insertPlainText("期日：");
    ui->textEdit_31->insertPlainText(data_timer.toHex());

    ui->textEdit_31->insertPlainText(" ");
    ui->textEdit_31->insertPlainText("类型：");
    ui->textEdit_31->insertPlainText(type.toHex());

    ui->textEdit_31->insertPlainText(" ");
    ui->textEdit_31->insertPlainText("框号：");
    ui->textEdit_31->insertPlainText(frame.toHex());

    ui->textEdit_31->insertPlainText(" ");
    ui->textEdit_31->insertPlainText("盘号：");
    ui->textEdit_31->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(39,READ);
    }else{
        set_color_for_textEdit(39,GREEN);
    }

    //ui->textEdit_22->moveCursor(start.Start);
}


    /*六号HUB*/
        if(cunt_hub_num == 6){
        ui->textEdit_32->clear();
            sleep(1000);


    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    ui->textEdit_32->insertPlainText("版本：");
    ui->textEdit_32->insertPlainText(version.toHex());

    ui->textEdit_32->insertPlainText(" ");
    ui->textEdit_32->insertPlainText("期日：");
    ui->textEdit_32->insertPlainText(data_timer.toHex());

    ui->textEdit_32->insertPlainText(" ");
    ui->textEdit_32->insertPlainText("类型：");
    ui->textEdit_32->insertPlainText(type.toHex());

    ui->textEdit_32->insertPlainText(" ");
    ui->textEdit_32->insertPlainText("框号：");
    ui->textEdit_32->insertPlainText(frame.toHex());

    ui->textEdit_32->insertPlainText(" ");
    ui->textEdit_32->insertPlainText("盘号：");
    ui->textEdit_32->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(38,READ);
    }else{
        set_color_for_textEdit(38,GREEN);
    }
    //ui->textEdit_23->moveCursor(start.Start);
}


    /*七号HUB*/
            if(cunt_hub_num == 7){
        ui->textEdit_29->clear();
            sleep(1000);


    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    ui->textEdit_29->insertPlainText("版本：");
    ui->textEdit_29->insertPlainText(version.toHex());

    ui->textEdit_29->insertPlainText(" ");
    ui->textEdit_29->insertPlainText("期日：");
    ui->textEdit_29->insertPlainText(data_timer.toHex());

    ui->textEdit_29->insertPlainText(" ");
    ui->textEdit_29->insertPlainText("类型：");
    ui->textEdit_29->insertPlainText(type.toHex());

    ui->textEdit_29->insertPlainText(" ");
    ui->textEdit_29->insertPlainText("框号：");
    ui->textEdit_29->insertPlainText(frame.toHex());

    ui->textEdit_29->insertPlainText(" ");
    ui->textEdit_29->insertPlainText("盘号：");
    ui->textEdit_29->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(35,READ);
    }else{
        set_color_for_textEdit(35,GREEN);
    }
    //ui->textEdit_24->moveCursor(start.Start);
}

    /*八号HUB*/
                if(cunt_hub_num == 8){
     ui->textEdit_33->clear();
         sleep(1000);


    version = src.mid(7,2);
    data_timer = src.mid(9,8);
    type = src.mid(17,1);
    frame = src.mid(18,1);
    tray = src.mid(19,1);

    ui->textEdit_33->insertPlainText("版本：");
    ui->textEdit_33->insertPlainText(version.toHex());

    ui->textEdit_33->insertPlainText(" ");
    ui->textEdit_33->insertPlainText("期日：");
    ui->textEdit_33->insertPlainText(data_timer.toHex());

    ui->textEdit_33->insertPlainText(" ");
    ui->textEdit_33->insertPlainText("类型：");
    ui->textEdit_33->insertPlainText(type.toHex());

    ui->textEdit_33->insertPlainText(" ");
    ui->textEdit_33->insertPlainText("框号：");
    ui->textEdit_33->insertPlainText(frame.toHex());

    ui->textEdit_33->insertPlainText(" ");
    ui->textEdit_33->insertPlainText("盘号：");
    ui->textEdit_33->insertPlainText(tray.toHex());
    if(tray.data()[0] == 0x00){
        set_color_for_textEdit(35,READ);
    }else{
        set_color_for_textEdit(35,GREEN);
    }
    //ui->textEdit_24->moveCursor(start.Start);
}
}
//数据发送
void Widget::jk_yi_jian_read_version_info(QByteArray src)
{

    unsigned char jk_kj_a6_1[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x01,0xAA,0x5A};
    unsigned char jk_kj_a6_2[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x02,0xF9,0x5A};
    unsigned char jk_kj_a6_3[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x03,0xC8,0x5A};
    unsigned char jk_kj_a6_4[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x04,0x5F,0x5A};
    unsigned char jk_kj_a6_5[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x05,0x6E,0x5A};
    unsigned char jk_kj_a6_6[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x06,0x3D,0x5A};
    unsigned char jk_kj_a6_7[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x07,0x0C,0x5A};
    unsigned char jk_kj_a6_8[9] = {0x7E,0x00,0x07,0xA6,0x10,0x02,0x08,0x22,0x5A};


    unsigned char jk_20_1[7] = {0x7e,0x00,0x05,0x20,0x01,0x71,0x5a};
    unsigned char jk_20_2[7] = {0x7e,0x00,0x05,0x20,0x02,0x22,0x5a};
    unsigned char jk_20_3[7] = {0x7e,0x00,0x05,0x20,0x03,0x13,0x5a};
    unsigned char jk_20_4[7] = {0x7e,0x00,0x05,0x20,0x04,0x84,0x5a};
    unsigned char jk_20_5[7] = {0x7e,0x00,0x05,0x20,0x05,0xB5,0x5a};
    unsigned char jk_20_6[7] = {0x7e,0x00,0x05,0x20,0x06,0xE6,0x5a};
    unsigned char jk_20_7[7] = {0x7e,0x00,0x05,0x20,0x07,0xD7,0x5a};
    unsigned char jk_20_8[7] = {0x7e,0x00,0x05,0x20,0x08,0xF9,0x5a};


    unsigned char jk_05_1[8] = {0x7E,0x00,0x06,0x05,0x01,0xFF,0xEF,0x5A};
    unsigned char jk_05_2[8] = {0x7E,0x00,0x06,0x05,0x02,0xFF,0xC2,0x5A};
    unsigned char jk_05_3[8] = {0x7E,0x00,0x06,0x05,0x03,0xFF,0x36,0x5A};
    unsigned char jk_05_4[8] = {0x7E,0x00,0x06,0x05,0x04,0xFF,0x98,0x5A};
    unsigned char jk_05_5[8] = {0x7E,0x00,0x06,0x05,0x05,0xFF,0x6C,0x5A};
    unsigned char jk_05_6[8] = {0x7E,0x00,0x06,0x05,0x06,0xFF,0x41,0x5A};
    unsigned char jk_05_7[8] = {0x7E,0x00,0x06,0x05,0x07,0xFF,0xB5,0x5A};
    unsigned char jk_05_8[8] = {0x7E,0x00,0x06,0x05,0x08,0xFF,0x2C,0x5A};


    unsigned char jk_v_a6_v_1[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x01,0x8F,0x5A};
    unsigned char jk_v_a6_v_2[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x02,0xDC,0x5A};
    unsigned char jk_v_a6_v_3[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x03,0xED,0x5A};
    unsigned char jk_v_a6_v_4[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x04,0x7A,0x5A};
    unsigned char jk_v_a6_v_5[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x05,0x4B,0x5A};
    unsigned char jk_v_a6_v_6[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x06,0x18,0x5A};
    unsigned char jk_v_a6_v_7[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x07,0x29,0x5A};
    unsigned char jk_v_a6_v_8[9] = {0x7E,0x00,0x07,0xA6,0x05,0x08,0x08,0x07,0x5A};


    switch ((unsigned char )src.data()[3]) {
        case 0x10:
            if(cunt_hub_num == 1){
                serial->write((char *)jk_kj_a6_1,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_1,7);
                ui->progressBar->setValue(20);
            }else if (cunt_hub_num == 2){
                serial->write((char *)jk_kj_a6_2,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_2,7);
                ui->progressBar->setValue(20);
            }else if (cunt_hub_num == 3){
                serial->write((char *)jk_kj_a6_3,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_3,7);
                ui->progressBar->setValue(20);
            }else if (cunt_hub_num == 4){
                serial->write((char *)jk_kj_a6_4,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_4,7);
                ui->progressBar->setValue(20);
            }else if (cunt_hub_num == 5){
                serial->write((char *)jk_kj_a6_5,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_5,7);
                ui->progressBar->setValue(20);
            }else if (cunt_hub_num == 6){
                serial->write((char *)jk_kj_a6_6,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_6,7);
                ui->progressBar->setValue(20);
            }else if (cunt_hub_num == 7){
                serial->write((char *)jk_kj_a6_7,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_7,7);
                ui->progressBar->setValue(20);
            }else if (cunt_hub_num == 8){
                serial->write((char *)jk_kj_a6_8,9);
                serial->waitForBytesWritten(send_time_count);
                sleep(delay_cnt);
                serial->write((char *)jk_20_8,7);
                ui->progressBar->setValue(20);
            }else{
                //no thing to do
            }

            break;
        case 0x20:
            if(cunt_hub_num == 1){
                serial->write((char *)jk_05_1,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else if (cunt_hub_num == 2){
                serial->write((char *)jk_05_2,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else if (cunt_hub_num == 3){
                serial->write((char *)jk_05_3,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else if (cunt_hub_num == 4){
                serial->write((char *)jk_05_4,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else if (cunt_hub_num == 5){
                serial->write((char *)jk_05_5,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else if (cunt_hub_num == 6){
                serial->write((char *)jk_05_6,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else if (cunt_hub_num == 7){
                serial->write((char *)jk_05_7,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else if (cunt_hub_num == 8){
                serial->write((char *)jk_05_8,8);
                sleep(delay_cnt);
                ui->progressBar->setValue(40);
            }else{
                //no thing to do
            }
            break;
        case 0x05:
            if(cunt_hub_num == 1){
                timer->stop();
                serial->write((char *)jk_v_a6_v_1,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else if (cunt_hub_num == 2){
                timer->stop();
                serial->write((char *)jk_v_a6_v_2,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else if (cunt_hub_num == 3){
                timer->stop();
                serial->write((char *)jk_v_a6_v_3,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else if (cunt_hub_num == 4){
                timer->stop();
                serial->write((char *)jk_v_a6_v_4,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else if (cunt_hub_num == 5){
                timer->stop();
                serial->write((char *)jk_v_a6_v_5,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else if (cunt_hub_num == 6){
                timer->stop();
                serial->write((char *)jk_v_a6_v_6,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else if (cunt_hub_num == 7){
                timer->stop();
                serial->write((char *)jk_v_a6_v_7,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else if (cunt_hub_num == 8){
                timer->stop();
                serial->write((char *)jk_v_a6_v_8,9);
                serial->waitForBytesWritten(send_time_count);
                disp_yi_jian_jk_read_version_info(src);
                //timer->stop();
                ui->progressBar->setValue(100);
                QMessageBox::information(NULL,"VERSION","一键读取版本成功",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            }else{
            //no thing to do
            }
            break;
        case 0xa6:
            if(cunt_hub_num == 1){
                sleep(2000);
                serial->write((char *)jk_20_1,7);
                ui->progressBar->setValue(60);
            }else if (cunt_hub_num == 2){
                sleep(2000);
                serial->write((char *)jk_20_2,7);
                ui->progressBar->setValue(60);
            }else if (cunt_hub_num == 3){
                sleep(2000);
                serial->write((char *)jk_20_3,7);
                ui->progressBar->setValue(60);
            }else if (cunt_hub_num == 4){
                sleep(2000);
                serial->write((char *)jk_20_4,7);
                ui->progressBar->setValue(60);
            }else if (cunt_hub_num == 5){
                sleep(2000);
                serial->write((char *)jk_20_5,7);
                ui->progressBar->setValue(60);
            }else if (cunt_hub_num == 6){
                sleep(2000);
                serial->write((char *)jk_20_6,7);
                ui->progressBar->setValue(60);
            }else if (cunt_hub_num == 7){
                sleep(2000);
                serial->write((char *)jk_20_7,7);
                ui->progressBar->setValue(60);
            }else if (cunt_hub_num == 8){
                sleep(2000);
                serial->write((char *)jk_20_8,7);
                ui->progressBar->setValue(60);
            }else{
            //no thing to do
            }
            break;
        default:
            if(cunt_hub_num == 1){
                serial->write((char *)jk_v_a6_v_1,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_1,8);
            }else if (cunt_hub_num == 2){
                serial->write((char *)jk_v_a6_v_2,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_2,8);
            }else if (cunt_hub_num == 3){
                serial->write((char *)jk_v_a6_v_3,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_3,8);
            }else if (cunt_hub_num == 4){
                serial->write((char *)jk_v_a6_v_4,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_4,8);
            }else if (cunt_hub_num == 5){
                serial->write((char *)jk_v_a6_v_5,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_5,8);
            }else if (cunt_hub_num == 6){
                serial->write((char *)jk_v_a6_v_6,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_6,8);
            }else if (cunt_hub_num == 7){
                serial->write((char *)jk_v_a6_v_7,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_7,8);
            }else if (cunt_hub_num == 8){
                serial->write((char *)jk_v_a6_v_8,9);
                sleep(delay_cnt);
                serial->write((char *)jk_05_8,8);
            }else{
            //no thing to do
            }
            break;
    }
    serial->waitForBytesWritten(send_time_count);
}


/*
 *串口接收处理程序 使用的是可读信号，只要串口接收到数据就进该处理流程
 */
void Widget::my_readuart()
{
    QByteArray requestData;

    requestData.resize(500);

    serial->waitForReadyRead(send_time_count);
    requestData = serial->readAll();
    sleep(delay_cnt);
    if(requestData.size() > 3)//if(requestData!= NULL)
    {
        switch(cmd_type){
            case LED_LIGHT_BUTTON:
                 product_test_led_on(requestData);
                 break;
            case LED_OFF_BUTTON:
                 product_test_led_off(requestData);
                 break;
            case READ_TRAY_VERSION:
                read_one_tray_version(requestData);
                 break;
            case READ_TRAY_PORT_INFO:
                 read_one_tray_port_info(requestData);
                 break;
            case HUB_YI_JIAN_READ_VERSION:
                 hub_yi_jian_read_version_info(requestData);
                 break;
            case JK_YI_JIAN_READ_VERSION_1:
                 jk_yi_jian_read_version_info(requestData);
                 break;
            default:
                 break;
        }
    }
   // sleep(delay_cnt);
    requestData.clear();
    serial->clear(QSerialPort::AllDirections);
    qDebug("data process ok \n");
}




/*LED 亮灯测试*/
void Widget::on_pushButton_5_clicked()
{
    const unsigned char led_light[8] = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
    ui->progressBar->setValue(0);
    if(serial->isOpen() == 0){
        QMessageBox::information(NULL,"ALARM","请先打开串口",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }else{
        cmd_type = LED_LIGHT_BUTTON;
        serial->write((char *)led_light,8);
        serial->waitForBytesWritten(send_time_count);
        timer->start(3000);
    }
}
/*LED 灭灯测试*/
void Widget::on_pushButton_clicked()
{
    const unsigned char led_light[8] = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
     ui->progressBar->setValue(0);

    if(serial->isOpen() == 0){
        QMessageBox::information(NULL,"ALARM","请先打开串口",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }else{
        cmd_type = LED_OFF_BUTTON;
        serial->write((char *)led_light,8);
        serial->waitForBytesWritten(send_time_count);
        timer->start(3000);
    }
}


/*读取单元板的软硬件版本号*/
void Widget::on_pushButton_7_clicked()
{
    unsigned char t_version_20[8] = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
     ui->progressBar->setValue(0);

    if(serial->isOpen() == 0){
        QMessageBox::information(NULL,"ALARM","请先打开串口",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }else{
        cmd_type = READ_TRAY_VERSION;
        serial->write((char *)t_version_20,8);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
    }
}

/*
 *读取单元板端口信息
 */
void Widget::on_pushButton_6_clicked()
{
    unsigned char t_read_port_20[8] = {0x7e,0x00,0x06,0x20,0x01,0x01,0x64,0x5a};
    ui->progressBar->setValue(0);
    //set_color_for_textEdit(2,READ);
    if(serial->isOpen() == 0){
        QMessageBox::information(NULL,"ALARM","请先打开串口",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }else{
        if(first_read_tary_v == 0){
            QMessageBox::information(NULL,"ALARM","必须先读取盘的版本号",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            return;
        }else{
            cmd_type = READ_TRAY_PORT_INFO;
            serial->write((char *)t_read_port_20,8);
            serial->waitForBytesWritten(send_time_count);
            timer->start(5000);
        }
    }

}


/*HUB一键读取版本号*/
void Widget::on_pushButton_13_clicked()
{
    unsigned char t_H_V_20[7] = {0x7e,0x00,0x05,0x20,0x01,0x71,0x5a};
    ui->progressBar->setValue(0);
    //set_color_for_textEdit(2,READ);
    if(serial->isOpen() == 0){
        QMessageBox::information(NULL,"ALARM","请先打开串口",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }else{
        cmd_type = HUB_YI_JIAN_READ_VERSION;
        serial->write((char *)t_H_V_20,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
    }
}

/*JK一键读取版本号*/
void Widget::on_pushButton_22_clicked()
{
    unsigned char jk_0x20_1[7] = {0x7e,0x00,0x05,0x20,0x01,0x71,0x5a};
    unsigned char jk_0x20_2[7] = {0x7e,0x00,0x05,0x20,0x02,0x22,0x5a};
    unsigned char jk_0x20_3[7] = {0x7e,0x00,0x05,0x20,0x03,0x13,0x5a};
    unsigned char jk_0x20_4[7] = {0x7e,0x00,0x05,0x20,0x04,0x84,0x5a};
    unsigned char jk_0x20_5[7] = {0x7e,0x00,0x05,0x20,0x05,0xB5,0x5a};
    unsigned char jk_0x20_6[7] = {0x7e,0x00,0x05,0x20,0x06,0xE6,0x5a};
    unsigned char jk_0x20_7[7] = {0x7e,0x00,0x05,0x20,0x07,0xD7,0x5a};
    unsigned char jk_0x20_8[7] = {0x7e,0x00,0x05,0x20,0x08,0xF9,0x5a};


    ui->progressBar->setValue(0);
    //set_color_for_textEdit(2,READ);
    if(serial->isOpen() == 0){
        QMessageBox::information(NULL,"ALARM","请先打开串口",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }else{
        //一号HUB开机
        cunt_hub_num = 1;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_1,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
         sleep(1000);
       // my_readuart();
        sleep(5000);

        //二号HUB开机
        cunt_hub_num = 2;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_2,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
        sleep(5000);

        //三号HUB开机
        cunt_hub_num = 3;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_3,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
        sleep(5000);

        //四号HUB开机
        cunt_hub_num = 4;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_4,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
        sleep(5000);

        //五号HUB开机
        cunt_hub_num = 5;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_5,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
        sleep(5000);

        //六号HUB开机
        cunt_hub_num = 6;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_6,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
        sleep(5000);

        //七号HUB开机
        cunt_hub_num = 7;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_7,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
        sleep(5000);

        //八号HUB开机
        cunt_hub_num = 8;
        cmd_type = JK_YI_JIAN_READ_VERSION;
        serial->write((char *)jk_0x20_8,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
        sleep(5000);
    }

}

void Widget::on_pushButton_17_clicked()
{
    unsigned char jk_0x20_1[7] = {0x7e,0x00,0x05,0x20,0x01,0x71,0x5a};
    ui->progressBar->setValue(0);
    if(serial->isOpen() == 0){
        QMessageBox::information(NULL,"ALARM","请先打开串口",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }else{
        cunt_hub_num = 1;
        cmd_type = JK_YI_JIAN_READ_VERSION_1;
        serial->write((char *)jk_0x20_1,7);
        serial->waitForBytesWritten(send_time_count);
        timer->start(5000);
    }
}
