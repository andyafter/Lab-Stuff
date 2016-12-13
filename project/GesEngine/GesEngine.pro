#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T18:17:02
#
#-------------------------------------------------

QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GesEngine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    artclient.cpp

HEADERS  += mainwindow.h \
    artclient.h

FORMS    += mainwindow.ui
