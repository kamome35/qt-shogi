! include( ../../lib_common.pri ) {
    error( Couldn't find the lib_common.pri file! )
}

TARGET   = shogi

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
