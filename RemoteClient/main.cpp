#include "remoteclientwindow.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));

    QApplication a(argc, argv);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    QApplication::setStyle(QStyleFactory::create("Fusion"));//设置风格
    QApplication::setPalette(QApplication::style()->standardPalette());
    RemoteClientWindow w;
    w.show();

    return a.exec();
}
