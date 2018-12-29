#include "clienwidget.h"
#include "ui_clienwidget.h"
#include <QHostAddress>


ClienWidget::ClienWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClienWidget)
{
    ui->setupUi(this);

    tcpSocket = NULL;

    setWindowTitle("我是客户端");
    //分配空间指定父对象
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::connected,
            [=]()
            {
                ui->textEditRead->setText("成功和服务器建立好连接");
            }
            );

    connect(tcpSocket, &QTcpSocket::readyRead,
                [=]()
                {
                    //获取对方发送的数据
                    QByteArray array = tcpSocket->readAll();
                    //追加到编辑区中
                    ui->textEditRead->append(array);
                }
            );
}

ClienWidget::~ClienWidget()
{
    delete ui;
}

void ClienWidget::on_buttonConnect_clicked()
{
    //获取服务器IP 和 端口
    QString ip = ui->lineEditIP->text();
    qint16 prot = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip), prot);
}

void ClienWidget::on_buttonSend_clicked()
{
    //获取编辑框内容
    QString str = ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}


void ClienWidget::on_buttonclose_clicked()
{
    //主动和对方断开连接
    if(NULL == tcpSocket)
    {
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
