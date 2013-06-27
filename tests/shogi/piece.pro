#-------------------------------------------------
#
# Project created by QtCreator 2013-06-11T22:16:07
#
#-------------------------------------------------
include(../../shogi.pri)

QT       += testlib
QT       -= gui

TARGET = tst_piecetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_piecetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

LIBS += -lshogi
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libshogi.a
