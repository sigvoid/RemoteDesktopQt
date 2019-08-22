#include "recievethread.h"

#include <QTime>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QCryptographicHash>
#include <QFile>

RecieveThread::RecieveThread(QByteArray &pixmapData, QMutex &pixmapDataMutex,
                             QHostAddress serverIp,ushort udpServerPort,
                             ushort udpLocalPort,int* fps, QObject *parent)
    :QThread(parent),pixmapData(pixmapData),pixmapDataMutex(pixmapDataMutex),
     serverIp(serverIp),udpServerPort(udpServerPort),udpLocalPort(udpLocalPort),
     fps(fps) {
    needRecieveFile = false;

}

void RecieveThread::run() {
    QUdpSocket udpSocket;
    udpSocket.bind(QHostAddress::AnyIPv4,udpLocalPort);
    udpSocket.setReadBufferSize(1024*1024*10);
    udpSocket.setSocketOption(QAbstractSocket::LowDelayOption,1);
    QTime recieveFileRecord;
    RecieveFileForm* recieveFileForm;
    while(1) {
        if(udpSocket.hasPendingDatagrams()) {
            QByteArray datagram = udpSocket.receiveDatagram().data();
            if(datagram != "ack") {  //收到数据包
                //创建包体
                Packet packet(datagram);
                //本块序号:总块数:本包数据大小:总数据大小:类型:参数1:参数2|(数据)
                //本块序号:总块数:本包数据大小:总数据大小:frame:0:0|(数据)
                //本块序号:总块数:本包数据大小:总数据大小:file:文件名:本包md5|(数据)

                //检查分包完整
                if(packet.isBadPacket()) {
                    return; //坏包不保存
                }

                //第一个分包，保存文件头参数
                if(blockVector.isEmpty()) {
                    maxBlocks = packet.maxBlocks;
                    totalSize = packet.totalSize;
                    blockVector.resize(maxBlocks+1);
                    if(packet.packetType == "file") {
                        needRecieveFile = true;
                        filename = packet.para1;
                        recieveFileRecord = QTime::currentTime();
                        qDebug()<<"recieving file "<<filename<<"...";
                        recieveFileForm = new RecieveFileForm(filename,
                                                              QString("%1M").arg((double)totalSize/1024/1024),
                                                              packet.blockSize,
                                                              maxBlocks);
                        recieveFileForm->setGeometry(200,150,400,180);
                        recieveFileForm->show();
                    }
                    //qDebug()<<"first block:" <<headPara;
                }

                //保存分包的参数
                int currentBlock = packet.currentBlock;
                int blockSize = packet.blockSize;
                //qDebug()<< "block: " << currentBlock << "/" << maxBlocks;
                //qDebug()<< "Block size=" << blockSize;
                //qDebug()<< "True block size=" << blockData.size();

                //如果是接收文件，需要再次检验文件MD5
                if(needRecieveFile == true) {
                    if(packet.isBadPacket(2)) {
                        return; //坏包不保存
                    }
                }

                //保存分包数据
                blockVector[currentBlock].resize(blockSize);
                blockVector[currentBlock].replace(0,blockSize,packet.blockRawData);

            } else {
                if(blockVector.isEmpty()) { //接收线程处于空闲状态
                    //qDebug()<< "ack next";
                    //尝试让服务器发送下一帧
                    while(udpSocket.hasPendingDatagrams()) udpSocket.receiveDatagram(); //清空遗留的请求
                    udpSocket.writeDatagram("next\0",5,serverIp,udpServerPort);
                } else {
                    //检查是否需要重发
                    int counter = 0;
                    for (int i=0; i<blockVector.count(); i++) {
                        if(blockVector[i].isEmpty()) {
                            //qDebug()<< "please resend" << i;
                            if(counter < 2) {
                                udpSocket.writeDatagram("resend:"+QString::number(i).toUtf8()+":",serverIp,udpServerPort);
                            }
                            counter++;

                        }
                    }
                    //设置下载进度
                    if(needRecieveFile == true)
                        recieveFileForm->setCurrentBlock(maxBlocks - counter);

                    if(counter == 0) {
                        //不用重发，进行组包
                        QByteArray composeData;
                        for (int i=0; i<blockVector.count(); i++) {
                            composeData.append(blockVector[i]);
                        }
                        if(needRecieveFile == false) {
                            //更新帧数据
                            pixmapDataMutex.lock();
                            pixmapData.resize(composeData.size());
                            pixmapData.replace(0,composeData.size(),composeData);
                            pixmapDataMutex.unlock();
                            if(fps != nullptr) *fps = *fps + 1;
                        } else {
                            //文件保存
                            QFile a("/home/save/"+filename);
                            a.open(QIODevice::WriteOnly);
                            a.write(composeData);
                            a.waitForBytesWritten(25);
                            a.close();
                            needRecieveFile = false;
                            qDebug()<<"file "<<filename<<" save cost " <<
                                    QTime::fromMSecsSinceStartOfDay(QTime::currentTime().msecsSinceStartOfDay() - recieveFileRecord.msecsSinceStartOfDay())
                                    .toString() ;
                            recieveFileForm->finishDownload();
                        }
                        //清空分包缓存
                        blockVector.resize(0);
                        //msleep(3);

                        //准备下一个整包接收
                        while(udpSocket.hasPendingDatagrams()) udpSocket.receiveDatagram(); //清空遗留的请求
                        udpSocket.writeDatagram("next\0",5,serverIp,udpServerPort);
                        //qDebug()<< "finish next frame";

                    } else {
                        while(udpSocket.hasPendingDatagrams()) udpSocket.receiveDatagram(); //清空遗留的请求
                    }
                }

            }

        }
    }

}

void RecieveThread::timeTest(bool mark) {
    static QTime timeRecord = QTime::currentTime();
    if(mark == true) {
        timeRecord = QTime::currentTime();
    } else if(timeRecord.isNull() == false) {
        qDebug()<<"time cost ms:"<<QTime::currentTime().msecsSinceStartOfDay() - timeRecord.msecsSinceStartOfDay();
        timeRecord = QTime();
    }
}
