#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T11:33:06
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += datavisualization
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GesEngine
TEMPLATE = app

LIBS += -lOpengl32
LIBS += -lglut

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    artclient.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    artclient.h

FORMS    += mainwindow.ui
