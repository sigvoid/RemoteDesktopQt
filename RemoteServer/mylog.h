#ifndef MYLOG_H
#define MYLOG_H

#include <QTextBrowser>
#include <QTime>


class myLog {
  public:
    myLog(QTextBrowser* logShow = nullptr);

    QTextBrowser* logShow;
    void setLog(QTextBrowser* logShow);
    void addLog(QString text);
};

#endif // MYLOG_H
