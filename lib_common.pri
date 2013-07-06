#Includes common configuration for all lib subdirectory .pro files.
TEMPLATE = lib
INCLUDEPATH += . ..

WARNINGS += -Wall

DESTDIR  = $$PWD/lib
CONFIG  += warn_on staticlib
LIBS    += -L$$DESTDIR
