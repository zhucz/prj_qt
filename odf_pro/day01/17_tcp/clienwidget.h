#ifndef CLIENWIDGET_H
#define CLIENWIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ClienWidget;
}

class ClienWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClienWidget(QWidget *parent = 0);
    ~ClienWidget();

private slots:
    void on_buttonSend_clicked();

    void on_buttonConnect_clicked();

    void on_buttonclose_clicked();

private:
    Ui::ClienWidget *ui;

    QTcpSocket *tcpSocket;//通信套接字
};

#endif // CLIENWIDGET_H
