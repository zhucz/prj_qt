#-------------------------------------------------
#
# Project created by QtCreator 2018-11-29T15:49:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 17_tcp
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    clienwidget.cpp

HEADERS  += widget.h \
    clienwidget.h

FORMS    += widget.ui \
    clienwidget.ui

CONFIG += C++11
