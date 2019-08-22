#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QCryptographicHash>
#include <QString>
#include <QByteArrayList>

class Packet {
  public:
    Packet(int currentBlock,int maxBlocks,int blockSize,int totalSize,QByteArray packetType,QByteArray blockRawData);
    Packet(int currentBlock, int maxBlocks, int totalSize, QByteArray packetType, QByteArray para1, QByteArray para2, QByteArray blockRawData);
    Packet(int currentBlock,int maxBlocks,int blockSize,int totalSize,QByteArray packetType,QByteArray para1,QByteArray para2,QByteArray blockRawData);
    Packet(QByteArray packetRawData);
    Packet(QByteArray head,QByteArray blockRawData);

    QByteArray rawDataMd5();
    QByteArray toByteArray();
    void printHead();
    bool isBadPacket(int HashPara=0);
    bool badPacket = false;

    //QByteArray head;
    int currentBlock;
    int maxBlocks;
    int blockSize;
    int totalSize;
    QByteArray packetType;
    QByteArray para1;
    QByteArray para2;

    QByteArray blockRawData;


};

#endif // PACKET_H
