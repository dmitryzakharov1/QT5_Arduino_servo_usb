#-------------------------------------------------
#
# Project created by QtCreator 2015-03-07T19:54:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = second
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

    LDFLAGS:  -L/usr/local/opt/qt5/lib
    CPPFLAGS: -I/usr/local/opt/qt5/include

QT += serialport
