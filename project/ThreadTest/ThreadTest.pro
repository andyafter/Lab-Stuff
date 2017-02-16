#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T16:13:07
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThreadTest
TEMPLATE = app

LIBS += -L\opencv\lib\libopencv_core320.dll.a
LIBS += -L\opencv\lib\libopencv_imgproc320.dll.a

SOURCES += main.cpp\
        mainwindow.cpp \
    myjob.cpp \
    myudp.cpp \
    myserver.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    myjob.h \
    myudp.h \
    myserver.h \
    mythread.h

FORMS    += mainwindow.ui
