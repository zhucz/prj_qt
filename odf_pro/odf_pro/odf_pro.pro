#-------------------------------------------------
#
# Project created by QtCreator 2017-06-17T09:53:46
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = odf_pro
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    thread.cpp \
    crc8.cpp

HEADERS  += widget.h \
    thread.h \
    cmd_type.h \
    crc8.h

FORMS    += widget.ui
