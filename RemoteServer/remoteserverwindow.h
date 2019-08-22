#ifndef REMOTESERVERWINDOW_H
#define REMOTESERVERWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include <QScreen>
#include <QDataStream>
#include <QNetworkInterface>
#include <QBuffer>
#include <QTimer>
#include <QMutex>
#include <QFileDialog>

#include "mylog.h"
#include "frametrans.h"
#include "autocapture.h"

namespace Ui {
class RemoteServerWindow;
}

class RemoteServerWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit RemoteServerWindow(QWidget *parent = nullptr);
    ~RemoteServerWindow();

    QString GetIpv4String();
  private slots:
    void on_startBt_clicked();

    void on_tcpServerConnected();
    void on_testBt_clicked();

    void on_clientTcpReadReady();
    void on_sendFileBt_clicked();

private:
    Ui::RemoteServerWindow *ui;
    QTcpServer tcpServer;
    QTcpSocket* clientTcpSocket;
    unsigned short tcpLocalPort;
    unsigned short udpLocalPort;
    QHostAddress clientIp;
    unsigned short tcpClientPort;
    unsigned short udpClientPort;

    //QPixmap mmp;
    QByteArray bytesPixmap;
    QMutex bytesPixmapMutex;
    autoCapture* autoCap;
    frameTrans* frameTranser;
    myLog aLog;
};

#endif // REMOTESERVERWINDOW_H
