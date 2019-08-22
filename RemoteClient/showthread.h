#ifndef SHOWTHREAD_H
#define SHOWTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QPixmap>
#include <QLabel>

class ShowThread : public QThread {
  public:
    explicit ShowThread(QLabel *showLb, QByteArray &pixmapData, QMutex &pixmapDataMutex, QObject *parent = nullptr);
    void run();


    QLabel* showLb;
    QByteArray &pixmapData;
    QMutex &pixmapDataMutex;
};

#endif // SHOWTHREAD_H
