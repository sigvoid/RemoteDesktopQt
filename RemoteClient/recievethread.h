#ifndef RECIEVETHREAD_H
#define RECIEVETHREAD_H

#include <QObject>
#include <QThread>
#include <QLabel>
#include <QHostAddress>
#include <QMutex>
#include <QMessageBox>
#include <packet.h>
#include <recievefileform.h>

class RecieveThread : public QThread {
  public:
    explicit RecieveThread(QByteArray &pixmapData, QMutex &pixmapDataMutex,
                           QHostAddress serverIp,ushort udpServerPort,
                           ushort udpLocalPort,int* fps = nullptr, QObject *parent = nullptr);
    void run();

    void timeTest(bool mark);

    QByteArray &pixmapData;
    QMutex &pixmapDataMutex;

    bool needRecieveFile;


    int* fps;
    QHostAddress serverIp;
    ushort udpLocalPort;
    ushort udpServerPort;

    QVector<QByteArray> blockVector;
    QString filename;
    QString blockMd5;
    //int currentBlock;
    int totalSize;
    int maxBlocks;
    QPixmap framePixmap;


};

#endif // RECIEVETHREAD_H
