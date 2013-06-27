#include "shogicomponent.h"
#include <QMetaType>

#include <shogi/component.h>

using namespace Shogi;

ShogiComponent::ShogiComponent(QObject *parent) :
    QThread(parent)
{
    component = new Shogi::Component;
}

ShogiComponent::~ShogiComponent()
{
}

void ShogiComponent::run()
{
    emit gameStart();

    forever {
        if (component->gameStatus() != StatusPlaying)
            break;
    }

    emit gameEnd();
}

bool ShogiComponent::movePiece(Player turn, const Shogi::Point &from, const Shogi::Point &to, PieceType piece_type)
{
    if (component->movePiece(turn, from, to, piece_type)) {
        emit pieceMoved(from, to, piece_type);
        return true;
    } else {
        return false;
    }
}
