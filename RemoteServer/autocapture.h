#ifndef AUTOCAPTURE_H
#define AUTOCAPTURE_H

#include <QObject>
#include <QThread>
#include <QBuffer>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QMutex>
#include <QApplication>
#include "windesktopdup.h"
#include "timetest.h"

class autoCapture :public QThread {
  public:
    autoCapture(QByteArray &bytes,QMutex &bytesMutex);
    void run();

  private:
    WinDesktopDup wdd;
    QByteArray &bytes;
    QMutex &bytesMutex;

};

#endif // AUTOCAPTURE_H
