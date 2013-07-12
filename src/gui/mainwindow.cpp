#include "mainwindow.h"
#include <QMetaType>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAction>
#include <QMenuBar>

#include <shogi/shogi.h>
#include <objs/human.h>
#include <objs/computerhuman.h>


using namespace Shogi;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    shogi_component(0)
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

    struct PieceInitList {
        Player owner;
        PieceType piece_type;
        Point point;
    };

    // 平手の駒配置
    const PieceInitList piece_init_type[] = {
        { Sente, PiecePawn,   Point(1, 7) },
        { Sente, PiecePawn,   Point(2, 7) },
        { Sente, PiecePawn,   Point(3, 7) },
        { Sente, PiecePawn,   Point(4, 7) },
        { Sente, PiecePawn,   Point(5, 7) },
        { Sente, PiecePawn,   Point(6, 7) },
        { Sente, PiecePawn,   Point(7, 7) },
        { Sente, PiecePawn,   Point(8, 7) },
        { Sente, PiecePawn,   Point(9, 7) },
        { Sente, PieceRook,   Point(2, 8) },
        { Sente, PieceBishop, Point(8, 8) },
        { Sente, PieceLance,  Point(1, 9) },
        { Sente, PieceKnight, Point(2, 9) },
        { Sente, PieceSilver, Point(3, 9) },
        { Sente, PieceGold,   Point(4, 9) },
        { Sente, PieceKing,   Point(5, 9) },
        { Sente, PieceGold,   Point(6, 9) },
        { Sente, PieceSilver, Point(7, 9) },
        { Sente, PieceKnight, Point(8, 9) },
        { Sente, PieceLance,  Point(9, 9) },
        { Gote,  PiecePawn,   Point(1, 3) },
        { Gote,  PiecePawn,   Point(2, 3) },
        { Gote,  PiecePawn,   Point(3, 3) },
        { Gote,  PiecePawn,   Point(4, 3) },
        { Gote,  PiecePawn,   Point(5, 3) },
        { Gote,  PiecePawn,   Point(6, 3) },
        { Gote,  PiecePawn,   Point(7, 3) },
        { Gote,  PiecePawn,   Point(8, 3) },
        { Gote,  PiecePawn,   Point(9, 3) },
        { Gote,  PieceRook,   Point(8, 2) },
        { Gote,  PieceBishop, Point(2, 2) },
        { Gote,  PieceLance,  Point(1, 1) },
        { Gote,  PieceKnight, Point(2, 1) },
        { Gote,  PieceSilver, Point(3, 1) },
        { Gote,  PieceGold,   Point(4, 1) },
        { Gote,  PieceKing,   Point(5, 1) },
        { Gote,  PieceGold,   Point(6, 1) },
        { Gote,  PieceSilver, Point(7, 1) },
        { Gote,  PieceKnight, Point(8, 1) },
        { Gote,  PieceLance,  Point(9, 1) },
    };

    // 駒を配置する
    const int count = sizeof(piece_init_type) / sizeof(piece_init_type[0]);
    for (int i = 0; i < count; ++i) {
        Piece piece(piece_init_type[i].owner, piece_init_type[i].piece_type);
        piece.setPoint(piece_init_type[i].point);
        shogi_component->setPiece(piece);
    }

    shogi_component->setPlayerName(Sente, gamestartdialog->playerName(Sente));
    shogi_component->setPlayerName(Gote, gamestartdialog->playerName(Gote));
    shogi_component->gameStartInit(gamestartdialog->timeLimit());
    player[Sente] = gamestartdialog->humanType(Sente) == HumanPlayer ?
                new Human(Sente, this) : new ComputerHuman(Sente, this);
    player[Gote] = gamestartdialog->humanType(Gote) == HumanPlayer ?
                new Human(Gote, this) : new ComputerHuman(Gote, this);
    player[Sente]->setShogiComponent(shogi_component);
    player[Gote]->setShogiComponent(shogi_component);
    info->setShogiComponent(shogi_component);
    board_view->setShogiComponent(shogi_component);

    connect(board_view, SIGNAL(selectedBoardPoint(Shogi::Point)), player[Sente], SLOT(selectionPoint(Shogi::Point)));
    connect(board_view, SIGNAL(selectedSenteHandPoint(Shogi::Point)), player[Sente], SLOT(selectionPoint(Shogi::Point)));

    connect(board_view, SIGNAL(selectedBoardPoint(Shogi::Point)), player[Gote], SLOT(selectionPoint(Shogi::Point)));
    connect(board_view, SIGNAL(selectedGoteHandPoint(Shogi::Point)), player[Gote], SLOT(selectionPoint(Shogi::Point)));

    connect(player[Sente], SIGNAL(selectPiece(const Shogi::Piece)), board_view, SLOT(selectedPiece(const Shogi::Piece)));
    connect(player[Gote], SIGNAL(selectPiece(const Shogi::Piece)), board_view, SLOT(selectedPiece(const Shogi::Piece)));

    /* 棋譜リストと同期 */
    connect(shogi_component, SIGNAL(recordAdded(Shogi::Record)), record, SLOT(recordUpdate(Shogi::Record)));
    connect(shogi_component, SIGNAL(pieceMoved(Shogi::Point,Shogi::Point,Shogi::PieceType)), board_view, SLOT(boardUpdate(Shogi::Point,Shogi::Point,Shogi::PieceType)));

    shogi_component->start();
    player[Sente]->start();
    player[Gote]->start();
}
