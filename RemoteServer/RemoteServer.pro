#-------------------------------------------------
#
# Project created by QtCreator 2019-08-01T01:03:59
#
#-------------------------------------------------

QT       += core gui network
LIBS += -ld3d11 -ld3dx11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_NO_WARNING_OUTPUT
#DEFINES += QT_NO_DEBUG_OUTPUT
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        frametrans.cpp \
        main.cpp \
        mylog.cpp \
        remoteserverwindow.cpp \
    autocapture.cpp \
    timetest.cpp \
    packet.cpp \
    windesktopdup.cpp

HEADERS += \
        frametrans.h \
        mylog.h \
        remoteserverwindow.h \
    autocapture.h \
    timetest.h \
    packet.h \
    windesktopdup.h \
    mousearray.h

FORMS += \
        remoteserverwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
