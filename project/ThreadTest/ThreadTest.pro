#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T16:13:07
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThreadTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myjob.cpp

HEADERS  += mainwindow.h \
    myjob.h

FORMS    += mainwindow.ui
