#include "mylog.h"
#include <QDebug>

myLog::myLog(QTextBrowser *logShow):logShow(logShow) {

}
void myLog::setLog(QTextBrowser *logShow) {
    this->logShow = logShow;
}

void myLog::addLog(QString text) {
    qDebug()<<text;
    if(logShow != nullptr)
        logShow->append(QTime::currentTime().toString() + ": " + text);
}
