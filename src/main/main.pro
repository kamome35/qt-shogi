include(../../shogi.pri)


INCLUDEPATH += . ..
LIBS += -lgui
LIBS += -lobjs
LIBS += -lshogi

TARGET = shogi

TEMPLATE = app
SOURCES += main.cpp
