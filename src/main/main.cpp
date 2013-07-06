#include <QTextCodec>
#include <QMetaType>

#include <shogi/shogi.h>

#ifndef SHOGI_NOT_GUI
#include <QtGui/QApplication>
#include <gui/mainwindow.h>
#else
#include <stdio.h>
#endif

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);

#ifndef SHOGI_NOT_GUI
    MainWindow w;
    w.show();

    return a.exec();
#else
    return 0;
#endif
}
