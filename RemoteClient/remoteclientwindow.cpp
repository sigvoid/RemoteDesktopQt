#include "remoteclientwindow.h"
#include "ui_remoteclientwindow.h"
#include <QMouseEvent>
#include <QThread>
#include <QTime>

RemoteClientWindow::RemoteClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteClientWindow) {
    ui->setupUi(this);
    ui->showLb->installEventFilter(this);
    connect(&fpsClock,&QTimer::timeout,this,&RemoteClientWindow::on_fpsClockTimeout);
    fpsClock.start(1000);
    connect(&tcpClient,&QTcpSocket::disconnected,this,&RemoteClientWindow::on_disconnected);
}

RemoteClientWindow::~RemoteClientWindow() {
    delete ui;
}

void RemoteClientWindow::on_connectBt_clicked() {
    //保存连接信息
    serverIp = QHostAddress(ui->serverIpLe->text());
    tcpServerPort = ui->tcpServerPortSb->text().toUShort();
    udpLocalPort = ui->udpLocalPortSb->value();
    udpServerPort = ui->udpServerPortSb->value();
    //隐藏控件
    ui->label->setHidden(true);
    ui->label_2->setHidden(true);
    ui->label_3->setHidden(true);
    ui->label_4->setHidden(true);
    ui->tcpServerPortSb->setHidden(true);
    ui->udpServerPortSb->setHidden(true);
    ui->udpLocalPortSb->setHidden(true);
    ui->serverIpLe->setHidden(true);
    ui->connectBt->setHidden(true);
    //开始udp接收线程
    udpRecieveThread = new RecieveThread(pixmapData,pixmapDataMutex,serverIp,
                                         udpServerPort,udpLocalPort,&fps);
    udpRecieveThread->start();
    //开始帧刷新线程
    showThread = new ShowThread(ui->showLb,pixmapData,pixmapDataMutex);
    showThread->start();
    //连接到服务器
    tcpClient.connectToHost(serverIp,tcpServerPort);
}
void RemoteClientWindow::on_fpsClockTimeout() {
    ui->fpsLb->setNum(fps);
    fps = 0;
}

//检测鼠标事件
bool RemoteClientWindow::eventFilter(QObject *obj, QEvent* e) {
    //QLabel *label = dynamic_cast<QLabel*>(obj);
    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(e);
    if(e->type() == QEvent::MouseButtonPress) { //按下
        qDebug()<< mouseEvent->x()<<","<<mouseEvent->y();
        QString cmd = QString("down:%1:%2:")
                      .arg((int)(mouseEvent->x()*2.4))
                      .arg((int)(mouseEvent->y()*2.4));
        tcpClient.write(cmd.toUtf8());
    }
    if(e->type() == QEvent::MouseButtonRelease) { //松开
        QString cmd = QString("up:%1:%2:")
                      .arg((int)(mouseEvent->x()*2.4))
                      .arg((int)(mouseEvent->y()*2.4));
        tcpClient.write(cmd.toUtf8());
    }
    if(e->type() == QEvent::MouseMove) { //移动
        QString cmd = QString("move:%1:%2:")
                      .arg((int)(mouseEvent->x()*2.4))
                      .arg((int)(mouseEvent->y()*2.4));
        tcpClient.write(cmd.toUtf8());
    }
    return QMainWindow::eventFilter(obj, e);
}

void RemoteClientWindow::on_disconnected() {
    udpRecieveThread->terminate();
    showThread->terminate();
    tcpClient.disconnect();
    ui->showLb->setPixmap(QPixmap());
    ui->label->setHidden(false);
    ui->label_2->setHidden(false);
    ui->label_3->setHidden(false);
    ui->label_4->setHidden(false);
    ui->tcpServerPortSb->setHidden(false);
    ui->udpServerPortSb->setHidden(false);
    ui->udpLocalPortSb->setHidden(false);
    ui->serverIpLe->setHidden(false);
    ui->connectBt->setHidden(false);

}

void RemoteClientWindow::timeTest(bool mark) {
    static QTime timeRecord = QTime::currentTime();
    if(mark == true) {
        timeRecord = QTime::currentTime();
    } else if(timeRecord.isNull() == false) {
        qDebug()<<"time cost ms:"<<QTime::currentTime().msecsSinceStartOfDay() - timeRecord.msecsSinceStartOfDay();
        timeRecord = QTime();
    }
}

