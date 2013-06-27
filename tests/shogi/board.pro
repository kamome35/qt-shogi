#-------------------------------------------------
#
# Project created by QtCreator 2013-05-18T02:49:12
#
#-------------------------------------------------
include(../../shogi.pri)

QT       += testlib
QT       -= gui

TARGET = tst_boardtest
CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tst_boardtest.cpp

LIBS += -lshogi
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libshogi.a




