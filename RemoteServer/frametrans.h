#ifndef FRAMETRANS_H
#define FRAMETRANS_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QApplication>
#include <QBuffer>
#include <QNetworkDatagram>
#include <QPixmap>
#include <QScreen>
#include <QMutex>
#include <QCryptographicHash>

#include "mylog.h"
#include "packet.h"

class frameTrans :public QThread {
  public:
    explicit frameTrans(QByteArray &bytesIn,QMutex &bytesInMutex, QHostAddress udpClientIp,
                        ushort udpClientPort, ushort udpLocalPort,
                        QObject *parent = nullptr);
    void run();

    QHostAddress udpClientIp;
    unsigned short udpClientPort;
    unsigned short udpLocalPort;
    //QPixmap &mmp;
    QByteArray &bytesIn;
    QMutex &bytesInMutex;

    bool needSendFile;
    QString fileName;
    QByteArray fileBytesIn;

    unsigned int sendFps;
    const int MAX_BLOCK_SIZE = 32000;

    myLog aLog;
    void timeTest(bool mark);
};

#endif // FRAMETRANS_H
