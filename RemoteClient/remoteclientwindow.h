#ifndef REMOTECLIENTWINDOW_H
#define REMOTECLIENTWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QScreen>
#include <QDataStream>
#include <QNetworkDatagram>
#include <QDebug>
#include <QBuffer>
#include "recievethread.h"
#include "showthread.h"

namespace Ui {
class RemoteClientWindow;
}

class RemoteClientWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit RemoteClientWindow(QWidget *parent = nullptr);
    ~RemoteClientWindow();

    void timeTest(bool mark);
    bool eventFilter(QObject *obj, QEvent *e);
  private slots:
    void on_connectBt_clicked();
    void on_fpsClockTimeout();

    void on_disconnected();
  private:
    Ui::RemoteClientWindow *ui;
    QTcpSocket tcpClient;

    QHostAddress serverIp;
    ushort tcpServerPort;
    ushort tcpLocalPort;
    ushort udpLocalPort;
    ushort udpServerPort;

    RecieveThread* udpRecieveThread;
    ShowThread* showThread;
    QByteArray pixmapData;
    QMutex pixmapDataMutex;

    QTimer fpsClock;
    QTimer updateTimer;
    int fps;
};

#endif // REMOTECLIENTWINDOW_H
