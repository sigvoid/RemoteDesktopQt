#include "frametrans.h"
#include <math.h>

frameTrans::frameTrans(QByteArray &bytesIn,QMutex &bytesInMutex, QHostAddress udpClientIp,
                       ushort udpClientPort, ushort udpLocalPort,
                       QObject *parent):QThread(parent),
    bytesIn(bytesIn),bytesInMutex(bytesInMutex),udpClientIp(udpClientIp),
    udpClientPort(udpClientPort),udpLocalPort(udpLocalPort) {
    needSendFile = false;


}

void frameTrans::run() {
    QUdpSocket clientSocket;
    //unsigned int delayMs = 1000/sendFps;
    clientSocket.bind(QHostAddress::Any,udpLocalPort);
    clientSocket.connectToHost(udpClientIp,udpClientPort);
    clientSocket.setReadBufferSize(1024*1024*10);
    clientSocket.setSocketOption(QAbstractSocket::LowDelayOption,1);
    aLog.addLog("frameTrans: client ip: " + udpClientIp.toString());
    aLog.addLog("frameTrans: client port: " + QString::number(udpClientPort));
    //Log.addLog("frameTrans: delayMs: " + QString::number(delayMs));
    while(1) {
        //读取要发送的数据
        QByteArray bytes;
        bytesInMutex.lock();
        if(needSendFile == true){
            bytes.resize(fileBytesIn.size());
            bytes.replace(0,fileBytesIn.size(),fileBytesIn);
            fileBytesIn.clear();
        }else{
            bytes.resize(bytesIn.size());
            bytes.replace(0,bytesIn.size(),bytesIn);
        }
        bytesInMutex.unlock();
        QBuffer buffer;
        buffer.setBuffer(&bytes);
        buffer.open(QIODevice::ReadWrite);

        //将要发送的udp分包列表
        QByteArrayList packetList;

        //读取包头需要的参数
        int totalSize = buffer.size(); //整包的大小
        int maxBlocks = floor((double)totalSize/(double)MAX_BLOCK_SIZE); //分包数最大下标
        for (int i=0; i<=maxBlocks; i++) {
            //获取当前分包的大小
            int blockSize;
            if(buffer.bytesAvailable() - MAX_BLOCK_SIZE > 0) {
                blockSize = MAX_BLOCK_SIZE;
            } else {
                blockSize = buffer.bytesAvailable();
            }
            //获取分包数据
            QByteArray blockRawData = buffer.read(MAX_BLOCK_SIZE);

            //创建包体
            Packet packet(i,maxBlocks,blockSize,totalSize,"frame",blockRawData);
            if(needSendFile){
                packet.packetType = "file";
                packet.para1 = fileName.toLatin1();
                packet.para2 = packet.rawDataMd5();
                //packet.printHead();
                //qDebug()<<"Raw"<<packet.blockRawData;
                //qDebug()<<"toByte"<<packet.toByteArray();
                if(i == maxBlocks) needSendFile = false;
            }

            //qDebug()<<"head>>"<<head;

            //分包加入到待发分包列表
            packetList.append(packet.toByteArray());
            if(packet.isBadPacket()) throw;
        }
        //发送全部分包
        for (int i=0; i<=maxBlocks; i++) {
            clientSocket.writeDatagram(packetList[i],udpClientIp,udpClientPort);
            //不发送全部 避免爆缓冲
            if(i>2)
                break;
        }
        //aLog.addLog("all sent");

        while(clientSocket.hasPendingDatagrams()) clientSocket.receiveDatagram(); //清空上次的请求
        while(1) {
            if(clientSocket.hasPendingDatagrams()) {
                //接收回应
                QByteArray respond;
                clientSocket.readDatagram(respond.data(),32);
                QString respondString = QString(respond.data());

                if(respondString.left(4) == "next") {  //所有分包接收完毕，开始准备下一个整包
                    //aLog.addLog("next frame");
                    msleep(5);
                    break;
                } else {                    //重发分包
                    QStringList resendList = respondString.split(":");
                    if(resendList[0] == "resend") {
                        for (int i=1; i<resendList.count()-1; i++) {
                            //aLog.addLog("resend " + resendList[i]);
                            clientSocket.writeDatagram(packetList[resendList[i].toInt()],udpClientIp,udpClientPort);
                        }
                        while(clientSocket.hasPendingDatagrams()) clientSocket.receiveDatagram();

                    } else {            //未知回应
                        aLog.addLog("bad packet(unrecognized):"+respondString);
                    }
                }
            } else {
                //发送心跳，要求客户端做出回应
                clientSocket.writeDatagram("ack",udpClientIp,udpClientPort);
                msleep(1);
            }

        }
    }
}

void frameTrans::timeTest(bool mark) {
    static QTime timeRecord = QTime::currentTime();
    if(mark == true) {
        timeRecord = QTime::currentTime();
    } else {
        qDebug()<<"time cost ms:"<<QTime::currentTime().msecsSinceStartOfDay() - timeRecord.msecsSinceStartOfDay();
    }
}
