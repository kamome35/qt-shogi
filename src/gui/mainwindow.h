#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QMainWindow>

#include <objs.h>

#include "information.h"
#include "recordwidget.h"
#include "gamestartdialog.h"
#include "boardview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ShogiComponent *shogiComponent() const { return shogi_component; }

public slots:
    void setup();

private:
    ShogiComponent *shogi_component;
    Human *sente;
    Human *gote;
    BoardView *board_view;
    Information *info;
    RecordWidget *record;
    GameStartDialog *gamestartdialog;
    QMenu *file_menu;
    QMenu *play_menu;
    QAction *load_action;
    QAction *save_action;
    QAction *exit_action;
    QAction *start_action;
};

#endif // GUI_MAINWINDOW_H
