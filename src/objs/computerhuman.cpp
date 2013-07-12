#include "computerhuman.h"
#include "shogi/move.h"

using namespace Shogi;

ComputerHuman::ComputerHuman(Player player, QObject *parent) :
    Human(player, parent)
{
    think = new QThread(this);

    connect(think, SIGNAL(started()), this, SLOT(doThinking()));
}

void ComputerHuman::setShogiComponent(ShogiComponent *shogi_component)
{
    connect(shogi_component, SIGNAL(changeTurn(Shogi::Player)), this, SLOT(startThinking()));

    Human::setShogiComponent(shogi_component);
}

void ComputerHuman::run()
{
    Human::run();
}

void ComputerHuman::startThinking()
{
    think->start();
}

void ComputerHuman::doThinking()
{
    // 自分の手番ではない場合は処理しない
    if (component->turn() != player) {
        think->quit();
        return;
    }

    PieceList piece_list = Move(component->board()).movablePieces(player);
    foreach (const Piece &piece, piece_list) {
        MovePointList move_points = Move(component->board()).movePoints(piece);
        foreach (const MovePoint &move_point, move_points) {
            select_piece = Piece();
            m_move_point = move_point;
            thinking = false;
            think->quit();
            return;
        }
    }
    think->quit();
}

void ComputerHuman::selectionPoint(const Point &point)
{
    Q_UNUSED(point);
}
