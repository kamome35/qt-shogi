#-------------------------------------------------
#
# Project
#
#-------------------------------------------------
include(../../shogi.pri)

TARGET   = shogi
QT      += core
TEMPLATE = lib
CONFIG  += staticlib


HEADERS += \
    shogi.h \
    piece.h \
    board.h \
    move.h \
    csa.h \
    record.h \
    component.h

SOURCES += \
    piece.cpp \
    board.cpp \
    move.cpp \
    csa.cpp \
    record.cpp \
    component.cpp \
    shogi.cpp

global_header.path = $$IDE_INCLUDE_PATH/shogi
global_header.files = $$HEADERS
INSTALLS += global_header


DESTDIR = $$IDE_LIBRARY_PATH














