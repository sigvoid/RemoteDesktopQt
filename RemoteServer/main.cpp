#include "remoteserverwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RemoteServerWindow w;
    w.show();

    return a.exec();
}
