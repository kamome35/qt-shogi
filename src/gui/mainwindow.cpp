#include "mainwindow.h"
#include <QMetaType>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAction>
#include <QMenuBar>

#include <shogi.h>
#include <objs.h>


using namespace Shogi;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    shogi_component(0),
    sente(0),
    gote(0)
{
    /* 盤 */
    board_view = new BoardView(this);

    /* 対局情報 */
    info = new Information(this);

    /* 棋譜 */
    record = new RecordWidget(this);

    gamestartdialog = new GameStartDialog(this);

    file_menu = menuBar()->addMenu(tr("ファイル(&F)"));
    play_menu = menuBar()->addMenu(tr("対局(&P)"));

    load_action = new QAction(tr("開く(&O)"), this);
    save_action = new QAction(tr("保存(&S)"), this);
    exit_action = new QAction(tr("終了(&X)"), this);
    start_action = new QAction(tr("対局開始(&S)"), this);

    setCentralWidget(board_view);
    addDockWidget(Qt::RightDockWidgetArea, info);
    addDockWidget(Qt::RightDockWidgetArea, record);

    file_menu->addAction(load_action);
    file_menu->addAction(save_action);
    file_menu->addSeparator();
    file_menu->addAction(exit_action);

    play_menu->addAction(start_action);

    connect(start_action, SIGNAL(triggered()), gamestartdialog, SLOT(open()));
    connect(gamestartdialog, SIGNAL(accepted()), this, SLOT(setup()));
    connect(exit_action, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup()
{
    shogi_component = new ShogiComponent(this);
    sente = new Human(Sente, this);
    gote = new Human(Gote, this);

    sente->setShogiComponent(shogi_component);
    gote->setShogiComponent(shogi_component);
    info->setShogiComponent(shogiComponent());
    board_view->setShogiComponent(shogiComponent());
    shogi_component->start();
    sente->start();
    gote->start();

    connect(board_view, SIGNAL(selectedBoardPoint(Shogi::Point)), sente, SLOT(selectionPoint(Shogi::Point)));
    connect(board_view, SIGNAL(selectedSenteHandPoint(Shogi::Point)), sente, SLOT(selectionPoint(Shogi::Point)));

    connect(board_view, SIGNAL(selectedBoardPoint(Shogi::Point)), gote, SLOT(selectionPoint(Shogi::Point)));
    connect(board_view, SIGNAL(selectedGoteHandPoint(Shogi::Point)), gote, SLOT(selectionPoint(Shogi::Point)));

    connect(sente, SIGNAL(selectPiece(const Shogi::Piece)), board_view, SLOT(selectedPiece(const Shogi::Piece)));
    connect(gote, SIGNAL(selectPiece(const Shogi::Piece)), board_view, SLOT(selectedPiece(const Shogi::Piece)));

    /* 棋譜リストと同期 */
    connect(shogiComponent(), SIGNAL(recordAdded(Shogi::Record)), record, SLOT(recordUpdate(Shogi::Record)));
    connect(shogiComponent(), SIGNAL(pieceMoved(Shogi::Point,Shogi::Point,Shogi::PieceType)), board_view, SLOT(boardUpdate(Shogi::Point,Shogi::Point,Shogi::PieceType)));
}
