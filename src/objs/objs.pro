! include( ../../lib_common.pri ) {
    error( Couldn't find the lib_common.pri file! )
}

TARGET   = objs

SOURCES += shogicomponent.cpp \
    human.cpp \
    computerhuman.cpp

HEADERS += shogicomponent.h \
    human.h \
    computerhuman.h
