#-------------------------------------------------
#
# Project created by QtCreator 2013-05-18T02:49:12
#
#-------------------------------------------------
include(../../shogi.pri)

QT       += core testlib
QT       -= gui

TARGET = tst_movetest
CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tst_movetest.cpp

LIBS += -lshogi
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libshogi.a
