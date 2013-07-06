include(../../shogi.pri)


INCLUDEPATH += . ..
LIBS += -lgui
LIBS += -lobjs
LIBS += -lshogi

TARGET = shogi

TEMPLATE = app
SOURCES += main.cpp

PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libgui.a
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libobjs.a
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libshogi.a
