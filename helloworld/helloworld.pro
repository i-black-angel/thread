#-------------------------------------------------
#
# Project created by QtCreator 2014-09-16T15:55:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld
TEMPLATE = app


SOURCES += main.cpp				\
        widget.cpp				\
        thread.cpp				\
        mutex.cpp

HEADERS  += widget.h

FORMS    += widget.ui
