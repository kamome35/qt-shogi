#include "piece.h"

using namespace Shogi;

namespace Shogi {
namespace PieceInternal {

class Piece
{
public:
    Piece() {}
    virtual ~Piece() {}
    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const = 0;

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    virtual bool canPromotion() const { return false; }

    /**
     * 駒の移動範囲を取得
     *
     * @return 移動範囲
     */
    inline MovingRangeList moveRanges() const { return moving_range; }


protected:
    MovingRangeList moving_range;
};

/**
 * 空
 *
 */
class PieceEmpty : public Piece
{
public:
    PieceEmpty() {}

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceEmpty; }
};

/**
 * 歩
 *
 */
class PiecePawn : public Piece
{
public:
    PiecePawn()
    {
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PiecePawn; }

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    virtual bool canPromotion() const { return true; }
};

/**
 * 香
 *
 */
class PieceLance : public Piece
{
public:
    PieceLance()
    {
        moving_range << MovingRange(Point( 0, 1), 8);   // 上
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceLance; }

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    virtual bool canPromotion() const { return true; }
};

/**
 * 桂
 *
 */
class PieceKnight : public Piece
{
public:
    PieceKnight()
    {
        moving_range << MovingRange(Point( 1, 2), 1);   // 右上
        moving_range << MovingRange(Point(-1, 2), 1);   // 左上
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceKnight; }

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    virtual bool canPromotion() const { return true; }
};

/**
 * 銀
 *
 */
class PieceSilver : public Piece
{
public:
    PieceSilver()
    {
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1,-1), 1);   // 右下
        moving_range << MovingRange(Point(-1,-1), 1);   // 左下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceSilver; }

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    virtual bool canPromotion() const { return true; }
};

/**
 * 金
 *
 */
class PieceGold : public Piece
{
public:
    PieceGold()
    {
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1, 0), 1);   // 右
        moving_range << MovingRange(Point(-1, 0), 1);   // 左
        moving_range << MovingRange(Point( 0,-1), 1);   // 下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceGold; }
};

/**
 * 飛
 *
 */
class PieceRook : public Piece
{
public:
    PieceRook()
    {
        moving_range << MovingRange(Point( 0, 1), 8);   // 上
        moving_range << MovingRange(Point( 0,-1), 8);   // 下
        moving_range << MovingRange(Point( 1, 0), 8);   // 右
        moving_range << MovingRange(Point(-1, 0), 8);   // 左
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceRook; }

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    virtual bool canPromotion() const { return true; }
};

/**
 * 角
 *
 */
class PieceBishop : public Piece
{
public:
    PieceBishop()
    {
        moving_range << MovingRange(Point( 1, 1), 8);   // 右上
        moving_range << MovingRange(Point(-1, 1), 8);   // 左上
        moving_range << MovingRange(Point( 1,-1), 8);   // 右下
        moving_range << MovingRange(Point(-1,-1), 8);   // 左下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceBishop; }

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    virtual bool canPromotion() const { return true; }
};

/**
 * 王
 *
 */
class PieceKing : public Piece
{
public:
    PieceKing()
    {
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1, 0), 1);   // 右
        moving_range << MovingRange(Point(-1, 0), 1);   // 左
        moving_range << MovingRange(Point( 1,-1), 1);   // 右下
        moving_range << MovingRange(Point( 0,-1), 1);   // 下
        moving_range << MovingRange(Point(-1,-1), 1);   // 左下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceKing; }
};

/**
 * と
 *
 */
class PiecePawnPromotion : public Piece
{
public:
    PiecePawnPromotion()
    {
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1, 0), 1);   // 右
        moving_range << MovingRange(Point(-1, 0), 1);   // 左
        moving_range << MovingRange(Point( 0,-1), 1);   // 下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PiecePawnPromotion; }
};

/**
 * 杏
 *
 */
class PieceLancePromotion : public Piece
{
public:
    PieceLancePromotion()
    {
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1, 0), 1);   // 右
        moving_range << MovingRange(Point(-1, 0), 1);   // 左
        moving_range << MovingRange(Point( 0,-1), 1);   // 下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceLancePromotion; }
};

/**
 * 圭
 *
 */
class PieceKnightPromotion : public Piece
{
public:
    PieceKnightPromotion()
    {
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1, 0), 1);   // 右
        moving_range << MovingRange(Point(-1, 0), 1);   // 左
        moving_range << MovingRange(Point( 0,-1), 1);   // 下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceKnightPromotion; }
};

/**
 * 全
 *
 */
class PieceSilverPromotion : public Piece
{
public:
    PieceSilverPromotion()
    {
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1, 0), 1);   // 右
        moving_range << MovingRange(Point(-1, 0), 1);   // 左
        moving_range << MovingRange(Point( 0,-1), 1);   // 下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceSilverPromotion; }
};

/**
 * 竜
 *
 */
class PieceRookPromotion : public Piece
{
public:
    PieceRookPromotion()
    {
        moving_range << MovingRange(Point( 0, 1), 8);   // 上
        moving_range << MovingRange(Point( 0,-1), 8);   // 下
        moving_range << MovingRange(Point( 1, 0), 8);   // 右
        moving_range << MovingRange(Point(-1, 0), 8);   // 左
        moving_range << MovingRange(Point( 1, 1), 1);   // 右上
        moving_range << MovingRange(Point(-1, 1), 1);   // 左上
        moving_range << MovingRange(Point( 1,-1), 1);   // 右下
        moving_range << MovingRange(Point(-1,-1), 1);   // 左下
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceRookPromotion; }
};

/**
 * 馬
 *
 */
class PieceBishopPromotion : public Piece
{
public:
    PieceBishopPromotion()
    {
        moving_range << MovingRange(Point( 1, 1), 8);   // 右上
        moving_range << MovingRange(Point(-1, 1), 8);   // 左上
        moving_range << MovingRange(Point( 1,-1), 8);   // 右下
        moving_range << MovingRange(Point(-1,-1), 8);   // 左下
        moving_range << MovingRange(Point( 0, 1), 1);   // 上
        moving_range << MovingRange(Point( 0,-1), 1);   // 下
        moving_range << MovingRange(Point( 1, 0), 1);   // 右
        moving_range << MovingRange(Point(-1, 0), 1);   // 左
    }

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    virtual PieceType type() const { return Shogi::PieceBishopPromotion; }
};

/**
 * 駒のインスタンスを取得する
 *
 * @param piece_type 駒種別
 * @return 駒オブジェクト
 */
Piece *getInstance(Shogi::PieceType piece_type)
{
    static Piece *instances[PieceTail];

    if (instances[piece_type])
        return instances[piece_type];


    switch (piece_type) {
    case Shogi::PieceEmpty:
        instances[piece_type] = new PieceEmpty();
        break;
    case Shogi::PiecePawn:
        instances[piece_type] = new PiecePawn();
        break;
    case Shogi::PieceLance:
        instances[piece_type] = new PieceLance();
        break;
    case Shogi::PieceKnight:
        instances[piece_type] = new PieceKnight();
        break;
    case Shogi::PieceSilver:
        instances[piece_type] = new PieceSilver();
        break;
    case Shogi::PieceGold:
        instances[piece_type] = new PieceGold();
        break;
    case Shogi::PieceRook:
        instances[piece_type] = new PieceRook();
        break;
    case Shogi::PieceBishop:
        instances[piece_type] = new PieceBishop();
        break;
    case Shogi::PieceKing:
        instances[piece_type] = new PieceKing();
        break;
    case Shogi::PiecePawnPromotion:
        instances[piece_type] = new PiecePawnPromotion();
        break;
    case Shogi::PieceLancePromotion:
        instances[piece_type] = new PieceLancePromotion();
        break;
    case Shogi::PieceKnightPromotion:
        instances[piece_type] = new PieceKnightPromotion();
        break;
    case Shogi::PieceSilverPromotion:
        instances[piece_type] = new PieceSilverPromotion();
        break;
    case Shogi::PieceRookPromotion:
        instances[piece_type] = new PieceRookPromotion();
        break;
    case Shogi::PieceBishopPromotion:
        instances[piece_type] = new PieceBishopPromotion();
        break;
    default:
        break;
    }

    return instances[piece_type];
}




} // namespace Internal
} // namespace Shogi

Piece::Piece() :
    internal(NULL),
    m_owner(NoPlayer),
    m_point(-1, -1)
{
    internal = PieceInternal::getInstance(PieceEmpty);
}

Piece::Piece(Player owner, PieceType piece_type) :
    internal(NULL),
    m_owner(owner),
    m_point(-1, -1)
{
    internal = PieceInternal::getInstance(piece_type);
}

Player Piece::owner() const
{
    return m_owner;
}

PieceType Piece::type() const
{
    Q_ASSERT(internal);
    return internal->type();
}

void Piece::setType(PieceType piece_type)
{
    internal = PieceInternal::getInstance(piece_type);
}

bool Piece::canPromotion() const
{
    Q_ASSERT(internal);
    return internal->canPromotion();
}

MovingRangeList Piece::moveRanges() const
{
    Q_ASSERT(internal);
    MovingRangeList moving_ranges;
    foreach(const MovingRange &move_range, internal->moveRanges()) {
        // 移動方向を変更する
        const Point &point = owner() != Sente ? move_range.point :
                                                move_range.point * -1;

        // 移動範囲を追加
        moving_ranges.append(MovingRange(point, move_range.range));
    }

    return moving_ranges;
}

void Piece::setPoint(const Point &point)
{
    Q_ASSERT(0 <= point.x() && point.x() <=9);
    Q_ASSERT(0 <= point.y() && point.y() <=9);

    m_point = point;
}

bool Piece::operator ==(const Piece &piece)
{
    if (this->type() != piece.type()) return false;
    if (this->owner() != piece.owner()) return false;
    if (this->point() != piece.point()) return false;

    return true;
}

bool Piece::operator !=(const Piece &piece)
{
    if (this->type() != piece.type()) return true;
    if (this->owner() != piece.owner()) return true;
    if (this->point() != piece.point()) return true;

    return false;
}

QDataStream &Piece::operator <<(QDataStream &out)
{
    out << this->m_owner;
    out << this->m_point;
    return out;
}

QDataStream &Piece::operator >>(QDataStream &in)
{
    in >> this->m_owner;
    in >> this->m_point;
    return in;
}
