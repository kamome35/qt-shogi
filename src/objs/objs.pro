#-------------------------------------------------
#
# Project created by QtCreator 2013-05-19T20:51:46
#
#-------------------------------------------------
include(../../shogi.pri)

TARGET   = objs
QT      += core gui
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += shogicomponent.cpp \
    human.cpp \
    computerhuman.cpp

HEADERS += shogicomponent.h \
    human.h \
    computerhuman.h

global_header.path = $$IDE_INCLUDE_PATH/objs
global_header.files = $$HEADERS
INSTALLS += global_header

DESTDIR = $$IDE_LIBRARY_PATH

LIBS += -lshogi
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libshogi.a
