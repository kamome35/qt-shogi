#include "record.h"

using namespace Shogi;


Record::Record() :
    _status(StatusError),
    _turn(NoPlayer),
    _from(-1, -1),
    _to(-1, -1),
    _piece_type(PieceEmpty),
    _sec(-1)
{
}

Record::Record(Player turn, const Point &from, const Point &to, PieceType piece_type, int sec) :
    _status(StatusPlaying),
    _turn(turn),
    _from(from),
    _to(to),
    _piece_type(piece_type),
    _sec(sec)
{
}

Record::Record(Player turn, GameStatus status) :
    _status(status),
    _turn(turn),
    _from(-1, -1),
    _to(-1, -1),
    _piece_type(PieceEmpty),
    _sec(-1)
{
}
