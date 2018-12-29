#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字,指定父对象让他自动回收空间
     tcpServer = new QTcpServer(this);
     tcpServer->listen(QHostAddress::Any, 8888);

     setWindowTitle("服务器：8888");

     connect(tcpServer, &QTcpServer::newConnection,
             [=]()
             {
                //取出建立好连接的套接字
                tcpSocket = tcpServer->nextPendingConnection();

                //获取对方的IP 和 端口
                QString ip = tcpSocket->peerAddress().toString();
                qint16 port = tcpSocket->peerPort();

                QString temp = QString("[%1：%2]:成功连接").arg(ip).arg(port);
                ui->textEditRead->setText(temp);

                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=]()
                        {
                            //从通信套接字中取出内容
                            QByteArray array = tcpSocket->readAll();
                            ui->textEditRead->append(array);

                        }
                        );

             }
             );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonSend_clicked()
{
    if(NULL == tcpSocket){
        return;
    }

    //获取编辑区的内容
    QString str = ui->textEditWrite->toPlainText();

    //给对方发送数据,使用套接字tcpSocket
    tcpSocket->write(str.toUtf8().data());

}






void Widget::on_buttonClose_clicked()
{
    if(NULL == tcpSocket){
        return;
    }

    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
}
