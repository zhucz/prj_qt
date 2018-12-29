QT += phonon
win32:contains(QT_CONFIG,opengl):QT += opengl

include(/yizhi/qt-everywhere-opensource-src-4.7.1/qt-everywhere-opensource-src-4.7.1/src/plugins/qpluginbase.pri)

TEMPLATE = lib

CONFIG += plugin debug_and_release build_all


TARGET = phonon_mp

HEADERS +=*.h

SOURCES +=*.cpp

LIBS += -Llibmplayer -lmplayer

SUBDIRS = libmplayer
