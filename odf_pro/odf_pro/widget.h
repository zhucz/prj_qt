#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>       //提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>   //提供系统中存在的串口信息

#include <QTime>

#include "crc8.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();



    void on_pushButton_5_clicked();



    void on_pushButton_7_clicked();

    void on_pushButton_22_clicked();

    /*自定义曹函数*/
    void my_readuart();//串口接收数据槽函数
    void product_test_led_on(QByteArray src);
    void product_test_led_off(QByteArray src);
    void read_one_tray_version(QByteArray src);
    void read_one_tray_port_info(QByteArray src);
    void disp_eid_port_info_colo(QByteArray src);

    void hub_yi_jian_read_version_info(QByteArray src);
    void disp_yi_jian_hub_read_version_info(QByteArray src);

    void jk_yi_jian_read_version_info(QByteArray src);
    void disp_yi_jian_jk_read_version_info(QByteArray src);

    void set_color_for_textEdit(int num,int color);
    void on_pushButton_clicked();

    void on_pushButton_13_clicked();


    /*定时器槽函数*/
    void my_uart_timer_update();
    void on_pushButton_17_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serial;
    unsigned char cmd_type;

    crc8 *calc_crc8 = new crc8;

    uint16_t send_time_count;
    uint16_t delay_cnt;
    uint16_t cunt_hub_num;

    QTimer *timer;

    uint8_t first_read_tary_v;
};

#endif // WIDGET_H
