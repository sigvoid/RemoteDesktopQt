#include "remoteserverwindow.h"
#include "ui_remoteserverwindow.h"

#include <QDebug>

#include <windows.h>

RemoteServerWindow::RemoteServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteServerWindow) {
    ui->setupUi(this);
    aLog.setLog(ui->logText);
    frameTranser->aLog.setLog(ui->logText);
    //获取本机ip
    ui->localIpLe->setText(GetIpv4String());
    connect(&tcpServer,&QTcpServer::newConnection,this,&RemoteServerWindow::on_tcpServerConnected);

}

RemoteServerWindow::~RemoteServerWindow() {
    delete ui;
}

void RemoteServerWindow::on_startBt_clicked() {
    if(tcpServer.isListening()) {
        aLog.addLog("停止服务");
        tcpServer.close();
        autoCap->terminate();
        frameTranser->terminate();
        //disconnect(clientTcpSocket,&QTcpSocket::readyRead,this,&RemoteServerWindow::on_clientTcpReadReady);
        clientTcpSocket->close();
        ui->startBt->setText("打开服务");
    } else {
        aLog.addLog("开始服务");

        autoCap = new autoCapture(bytesPixmap,bytesPixmapMutex);
        autoCap->start();

        tcpLocalPort = ui->tcpLocalPortLe->text().toUShort();
        tcpServer.listen(QHostAddress::AnyIPv4,tcpLocalPort);
        udpClientPort = ui->udpClientPortLe->text().toUShort();
        udpLocalPort = ui->udpLocalPortLe->text().toUShort();
        ui->startBt->setText("停止服务");
    }
    //udpSocket.bind(QHostAddress::Any,ui->portLe->text().toUShort());
    //connect(&udpSocket,&QUdpSocket::connected,this,&RemoteServerWindow::on_udpSocketConnected);
}

void RemoteServerWindow::on_tcpServerConnected() {
    aLog.addLog("客户端连接，准备发送屏幕数据");
    clientTcpSocket = tcpServer.nextPendingConnection();
    clientIp = clientTcpSocket->peerAddress();
    tcpClientPort = clientTcpSocket->peerPort();
    connect(clientTcpSocket,&QTcpSocket::readyRead,this,&RemoteServerWindow::on_clientTcpReadReady);

    frameTranser = new frameTrans(bytesPixmap,bytesPixmapMutex,clientIp,udpClientPort,udpLocalPort);
    frameTranser->start();

}
void RemoteServerWindow::on_clientTcpReadReady(){
    //qDebug()<<"tcp msg:";
        QString cmdRecv(clientTcpSocket->readAll());
        QStringList cmdList = cmdRecv.split(':');
        if(cmdList.count() == 4){
            int x = cmdList[1].toInt();
            int y = cmdList[2].toInt();
            if(x>0 && y>0){
                if(cmdList[0] == "down"){
                    //qDebug()<<"down"<<cmdList[1].toInt()<<","<<cmdList[2].toInt();
                    SetCursorPos(cmdList[1].toInt(),cmdList[2].toInt());
                    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
                }else if(cmdList[0] == "up"){
                    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
                }else if(cmdList[0] == "move"){
                    //qDebug()<<"down"<<cmdList[1].toInt()<<","<<cmdList[2].toInt();
                    SetCursorPos(cmdList[1].toInt(),cmdList[2].toInt());
                }
            }
        }
}
QString RemoteServerWindow::GetIpv4String() {
    QList<QHostAddress> vAddressList = QNetworkInterface::allAddresses();
    for(int i=0; i<vAddressList.size(); i++) {
        qDebug()<<vAddressList.at(i);
        if((vAddressList.at(i)!=QHostAddress::LocalHost)&&(vAddressList.at(i).protocol()==QAbstractSocket::IPv4Protocol)) {
            return vAddressList.at(i).toString();
        }
    }
    return "No IP Found.";
}

void RemoteServerWindow::on_testBt_clicked() {
    QByteArray bytes;
    QBuffer buffer;
    buffer.setBuffer(&bytes);
    //QPixmap mmp.save(&buffer, "JPG");
    buffer.open(QIODevice::ReadWrite);
    qDebug()<<buffer.size();
    qDebug()<<bytes.size();
    qDebug()<<buffer.bytesAvailable();
    qDebug()<<buffer.read(50);
    qDebug()<<buffer.bytesAvailable();

}

void RemoteServerWindow::on_sendFileBt_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"选择发送文件");
    QFile a(filename);
    a.open(QIODevice::ReadOnly);
    frameTranser->fileBytesIn = a.readAll();
    a.flush();
    a.close();
    filename = filename.right(filename.length() - filename.lastIndexOf('/') -1);
    aLog.addLog(filename);
    frameTranser->fileName = filename;
    frameTranser->needSendFile = true;
}
