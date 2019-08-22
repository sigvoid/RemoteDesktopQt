#include "timetest.h"

TimeTest::TimeTest(QString name):name(name)
{
    in();
}

void TimeTest::in(){
    timeRecord = QTime::currentTime();
}

void TimeTest::out() {
    if(timeRecord.isNull() == false)
        qDebug()<<name<<" cost ms:"<<QTime::currentTime().msecsSinceStartOfDay() - timeRecord.msecsSinceStartOfDay();
}
