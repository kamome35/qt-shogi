! include( ../../lib_common.pri ) {
    error( Couldn't find the lib_common.pri file! )
}

TARGET   = gui

SOURCES += mainwindow.cpp \
    information.cpp \
    gamestartdialog.cpp \
    boardview.cpp \
    recordwidget.cpp

HEADERS  += mainwindow.h \
    information.h \
    gamestartdialog.h \
    boardview.h \
    recordwidget.h

FORMS += \
    gamestartdialog.ui

