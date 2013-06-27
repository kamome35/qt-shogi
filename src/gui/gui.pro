#-------------------------------------------------
#
# Project
#
#-------------------------------------------------
include(../../shogi.pri)

TARGET   = gui
QT      += core gui
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += mainwindow.cpp \
    information.cpp \
    gamestartdialog.cpp \
    boardview.cpp \
    squareitem.cpp \
    recordwidget.cpp

HEADERS  += mainwindow.h \
    information.h \
    gamestartdialog.h \
    boardview.h \
    squareitem.h \
    recordwidget.h


FORMS += \
    gamestartdialog.ui

global_header.path = $$IDE_INCLUDE_PATH/gui
global_header.files = $$HEADERS
INSTALLS += global_header

DESTDIR = $$IDE_LIBRARY_PATH






