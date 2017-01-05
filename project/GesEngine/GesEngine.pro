#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T11:33:06
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GesEngine
TEMPLATE = app

LIBS += -lOpengl32

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui
