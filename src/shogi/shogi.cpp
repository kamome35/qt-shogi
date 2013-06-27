#include <QDataStream>
#include "shogi.h"
#include "piece.h"

using namespace Shogi;


namespace Shogi {


String pieceTypeString(PieceType piece_type)
{
    switch (piece_type) {
    case PieceEmpty:
        return " * ";
        break;
    case PiecePawn:
        return "FU";
        break;
    case PieceLance:
        return "KY";
        break;
    case PieceKnight:
        return "KE";
        break;
    case PieceSilver:
        return "GI";
        break;
    case PieceGold:
        return "KI";
        break;
    case PieceRook:
        return "HI";
        break;
    case PieceBishop:
        return "KA";
        break;
    case PieceKing:
        return "OU";
        break;
    case PiecePawnPromotion:
        return "TO";
        break;
    case PieceLancePromotion:
        return "NY";
        break;
    case PieceKnightPromotion:
        return "NK";
        break;
    case PieceSilverPromotion:
        return "NG";
        break;
    case PieceRookPromotion:
        return "RY";
        break;
    case PieceBishopPromotion:
        return "UM";
        break;
    default:
        Q_ASSERT_X(false, "pieceTypeString", "Unknwon piece type.");
        break;
    }

    return " * ";
}

String gameStatusString(GameStatus status)
{
    switch (status) {
    case StatusToryo:
        return "TORYO";
    case StatusChudan:
        return "CHUDAN";
    case StatusSennichite:
        return "SENNICHITE";
    case StatusTimeUp:
        return "TIMEUP";
    case StatusIllegalMove:
        return "ILLEGALMOVE";
    case StatusJishogi:
        return "JISHOGI";
    case StatusKachi:
        return "KACHI";
    case StatusHikiwake:
        return "HIKIWAKE";
    case StatusTsumi:
        return "TSUMI";
    case StatusFuzumi:
        return "FUZUMI";
    case StatusStandBy:
    case StatusPlaying:
    case StatusError:
    default:
        return "ERROR";
    }
}

} // namespace Shogi

QDataStream &operator <<(QDataStream &out, const Player &data)
{
    out << data;
    return out;
}

QDataStream &operator >>(QDataStream &in, Player &data)
{
    in >> data;
    return in;
}

QDataStream &operator <<(QDataStream &out, const PieceType &data)
{
    out << data;
    return out;
}

QDataStream &operator >>(QDataStream &in, PieceType &data)
{
    in >> data;
    return in;
}

QDataStream &operator <<(QDataStream &out, const GameType &data)
{
    out << data;
    return out;
}

QDataStream &operator >>(QDataStream &in, GameType &data)
{
    in >> data;
    return in;
}

QDataStream &operator <<(QDataStream &out, const PieceTypeList &data)
{
    out << data;
    return out;
}

QDataStream &operator >>(QDataStream &in, PieceTypeList &data)
{
    in >> data;
    return in;
}

QDataStream &operator <<(QDataStream &out, const MovePoint &data)
{
    out << data.from;
    out << data.to;
    out << data.piece_type;
    return out;
}

QDataStream &operator >>(QDataStream &in, MovePoint &data)
{
    in >> data.from;
    in >> data.to;
    in >> data.piece_type;
    return in;
}

QDataStream &operator <<(QDataStream &out, const MovePointList &data)
{
    out << data;
    return out;
}

QDataStream &operator >>(QDataStream &in, MovePointList &data)
{
    in >> data;
    return in;
}

QDataStream &operator <<(QDataStream &out, const MovingRange &data)
{
    out << data.point;
    out << data.range;
    return out;
}

QDataStream &operator >>(QDataStream &in, MovingRange &data)
{
    in >> data.point;
    in >> data.range;
    return in;
}

QDataStream &operator <<(QDataStream &out, const MovingRangeList &data)
{
    out << data;
    return out;
}

QDataStream &operator >>(QDataStream &in, MovingRangeList &data)
{
    in >> data;
    return in;
}
