#include "packet.h"
#include <QDebug>

//从给定参数生成udp数据包
Packet::Packet(int currentBlock, int maxBlocks, int blockSize, int totalSize, QByteArray packetType, QByteArray blockRawData)
    :currentBlock(currentBlock),maxBlocks(maxBlocks),blockSize(blockSize),
     totalSize(totalSize),packetType(packetType),para1("0"),para2("0"),blockRawData(blockRawData) {
}
Packet::Packet(int currentBlock,int maxBlocks,int blockSize,int totalSize,QByteArray packetType,QByteArray para1,QByteArray para2,QByteArray blockRawData)
    :currentBlock(currentBlock),maxBlocks(maxBlocks),blockSize(blockSize),
     totalSize(totalSize),packetType(packetType),para1(para1),para2(para2),blockRawData(blockRawData) {
}
Packet::Packet(int currentBlock,int maxBlocks,int totalSize,QByteArray packetType,QByteArray para1,QByteArray para2,QByteArray blockRawData)
    :currentBlock(currentBlock),maxBlocks(maxBlocks),
     totalSize(totalSize),packetType(packetType),para1(para1),para2(para2),blockRawData(blockRawData) {
    blockSize = blockRawData.size();
}
Packet::Packet(QByteArray head, QByteArray blockRawData):Packet(head + blockRawData) {

}

//从一个完整的udp包中解析文件头和数据
Packet::Packet(QByteArray packetRawData) {
    int cutPos = packetRawData.indexOf('|');
    QByteArrayList headParaList = packetRawData.left(cutPos).split(':');
    if(headParaList.count() == 7) {
        blockRawData = packetRawData.right(packetRawData.size()-cutPos-1);
        currentBlock = headParaList[0].toInt();
        maxBlocks = headParaList[1].toInt();
        blockSize = headParaList[2].toInt();
        totalSize = headParaList[3].toInt();
        packetType = headParaList[4];
        para1 = headParaList[5];
        para2 = headParaList[6];
    } else {
        qDebug()<<packetRawData;
        badPacket = true;
    }

}
//计算udp包中数据段的MD5
QByteArray Packet::rawDataMd5() {
    return QCryptographicHash::hash(blockRawData,QCryptographicHash::Md5).toHex();
}
//把数据包转换为用于socket发送的QByteArray
QByteArray Packet::toByteArray() {
    //本块序号:总块数:本包数据大小:总数据大小:类型:参数1:参数2|(数据)
    //本块序号:总块数:本包数据大小:总数据大小:frame:null:null|(数据)
    //本块序号:总块数:本包数据大小:总数据大小:file:文件名:本包md5|(数据)
    QByteArray head = QString("%1:%2:%3:%4")
                      .arg(QString::number(currentBlock))
                      .arg(QString::number(maxBlocks))
                      .arg(QString::number(blockSize))
                      .arg(QString::number(totalSize)).toLatin1();
    head.append(':' + packetType + ':' + para1 + ':' + para2 + '|');
    return head + blockRawData;
}
//打印文件头用于调试
void Packet::printHead() {
    qDebug()<<"currentBlock:"<<currentBlock;
    qDebug()<< "maxBlocks"<< maxBlocks;
    qDebug()<< "blockSize"<< blockSize;
    qDebug()<< "totalSize"<< totalSize;
    qDebug()<< "packetType"<< packetType;
    qDebug()<< "para1"<< para1;
    qDebug()<< "para2"<< para2;
}
//通过参数数、大小、MD5 检测udp数据包是否完整
bool Packet::isBadPacket(int HashPara) {
    if(badPacket == true) {
        qDebug()<< "bad para" ;
        return true;
    }
    if(blockRawData.size() != blockSize) {
        qDebug()<< "bad size" ;
        return true;
    }
    if(HashPara == 1) {
        QByteArray trueHash = QCryptographicHash::hash(blockRawData,QCryptographicHash::Md5).toHex();
        if(trueHash != para1) {
            qDebug()<< "bad hash:"<< trueHash<< "vs" <<para1;
            //qDebug()<<blockRawData;
            return true;
        }
    } else if(HashPara == 2) {
        QByteArray trueHash = QCryptographicHash::hash(blockRawData,QCryptographicHash::Md5).toHex();
        if(trueHash != para2) {
            qDebug()<< "bad hash:"<< trueHash<< "vs" <<para2;
            //qDebug()<<blockRawData;
            return true;
        }
    }
    return false;
}
