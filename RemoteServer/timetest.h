#ifndef TIMETEST_H
#define TIMETEST_H

#include <QDebug>
#include <QTime>

class TimeTest
{
public:
    TimeTest(QString name);
    void in();
    void out();

    QString name;
    QTime timeRecord;
};

#endif // TIMETEST_H
