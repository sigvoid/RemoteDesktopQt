#include "autocapture.h"

autoCapture::autoCapture(QByteArray &bytes,QMutex &bytesMutex):QThread(),bytes(bytes),bytesMutex(bytesMutex) {

}

void autoCapture::run() {
    wdd.Initialize();
    while (1) {
        /***  screenshot  ***/
        //TimeTest ttall("host frame max");
        //TimeTest ssrecord("screenshot");
        //QPixmap mmp = QGuiApplication::primaryScreen()->grabWindow(0).scaledToHeight(450,Qt::SmoothTransformation);
        wdd.CaptureNext();
        QImage image((const unsigned char*)wdd.Latest.Buf.data(), wdd.Latest.Width, wdd.Latest.Height, QImage::Format_RGB32);
        image = image.scaledToHeight(450,Qt::SmoothTransformation);
        //QPixmap mmp = QApplication::screens().at(0)->grabWindow(0).scaledToHeight(450,Qt::SmoothTransformation);


        //ssrecord.out();
        /***  screenshot  ***/
        QBuffer buffer;
        QByteArray tempBytes;
        buffer.setBuffer(&tempBytes);
        //TimeTest tt2("save pic");
        image.save(&buffer,"PPM"); //cost 11ms
        tempBytes = qCompress(tempBytes,1);
        //tt2.out();
        //ttall.out();

        bytesMutex.lock();
        bytes.resize(tempBytes.size());
        bytes.replace(0,tempBytes.size(),tempBytes);
        bytesMutex.unlock();
    }
}
