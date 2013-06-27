include(../../shogi.pri)

TARGET = shogi
QT      += core
TEMPLATE = app

#DESTDIR = $$IDE_APP_PATH

SOURCES += main.cpp
CONFIG  += app_bundle

LIBS += -lgui
LIBS += -lobjs
LIBS += -lshogi

PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libgui.a
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libobjs.a
PRE_TARGETDEPS += $$IDE_LIBRARY_PATH/libshogi.a
