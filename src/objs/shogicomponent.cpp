#include "shogicomponent.h"

#include <shogi/shogi.h>
#include <shogi/component.h>

using namespace Shogi;

ShogiComponent::ShogiComponent(QObject *parent) :
    QThread(parent),
    Component()
{
}

ShogiComponent::~ShogiComponent()
{
}

void ShogiComponent::setGameStatus(GameStatus status)
{
    Shogi::Component::setGameStatus(status);
    emit changeGameStatus(status);
}

bool ShogiComponent::movePiece(Player turn, const Point &from, const Point &to, PieceType piece_type)
{
    // 駒を移動する
    if (Component::movePiece(turn, from, to, piece_type)) {
        emit pieceMoved(from, to, piece_type);
        emit changeTurn(this->turn());
        return true;
    } else {
        return false;
    }
}

void ShogiComponent::run()
{
    // ゲーム開始を通知
    emit gameStart();

    // ゲーム状態を監視する
    forever {
        if (gameStatus() != StatusPlaying)
            break;

        msleep(100);
    }

    // ゲーム終了を通知
    emit gameEnd();
}
