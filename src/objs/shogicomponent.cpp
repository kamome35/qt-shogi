#include "shogicomponent.h"
#include <QMetaType>

#include <shogi.h>

using namespace Shogi;

ShogiComponent::ShogiComponent(QObject *parent) :
    QThread(parent),
    Component()
{
}

ShogiComponent::~ShogiComponent()
{
}

void ShogiComponent::run()
{
    // ゲーム開始を通知
    emit gameStart();

    // ゲーム状態を監視する
    forever {
        if (gameStatus() != StatusPlaying)
            break;
    }

    // ゲーム終了を通知
    emit gameEnd();
}

bool ShogiComponent::movePiece(Player turn, const Shogi::Point &from, const Shogi::Point &to, PieceType piece_type)
{
    // 駒を移動する
    if (Component::movePiece(turn, from, to, piece_type)) {
        emit pieceMoved(from, to, piece_type);
        return true;
    } else {
        return false;
    }
}
