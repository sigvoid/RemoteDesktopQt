#include "showthread.h"

#include <QTime>
#include <QDebug>

ShowThread::ShowThread(QLabel* showLb,QByteArray &pixmapData,
                       QMutex &pixmapDataMutex,QObject *parent)
    :QThread(parent),showLb(showLb),pixmapData(pixmapData),
     pixmapDataMutex(pixmapDataMutex) {

}

void ShowThread::run() {
    while(1) {
        pixmapDataMutex.lock();
        if(pixmapData.isEmpty() == false) {
            QByteArray tempPixmapData;
            tempPixmapData.resize(pixmapData.size());
            tempPixmapData.replace(0,pixmapData.size(),pixmapData);
            pixmapDataMutex.unlock();

            tempPixmapData = qUncompress(tempPixmapData);
            QPixmap framePixmap;
            framePixmap.loadFromData(tempPixmapData,"PPM");

            showLb->setPixmap(framePixmap);
        } else {
            pixmapDataMutex.unlock();
        }
        //msleep(20);
    }
}
