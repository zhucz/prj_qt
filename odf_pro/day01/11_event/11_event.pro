#-------------------------------------------------
#
# Project created by QtCreator 2018-11-28T19:30:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 11_event
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    mylable.cpp \
    mybutton.cpp

HEADERS  += mywidget.h \
    mylable.h \
    mybutton.h

FORMS    += mywidget.ui

CONFIG += C++11
