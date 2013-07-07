#ifndef SHOGI_PIECE_H
#define SHOGI_PIECE_H

#include "shogi.h"

namespace Shogi {

/**
 * 駒情報の各駒にによる内部の動きの違いを定義する
 */
namespace PieceInternal {
class Piece;
} // namespace Internal

/**
 * 駒データ
 *
 * 駒の種別や配置座標などを管理するクラス
 */
class Piece
{
public:

    /**
     * 駒
     *
     */
    Piece();
    Piece(Player owner, PieceType piece_type);

    /**
     * 駒の所有者を取得
     *
     * @return Player
     */
    Player owner() const;

    /**
     * 駒種別を取得する
     *
     * @return  駒種別
     */
    PieceType type() const;

    /**
     * 駒種別を変更する
     *
     * @param piece_type 駒種別
     */
    void setType(PieceType piece_type);

    /**
     * 昇格可能か？
     *
     * @return  true 昇格可能
     */
    bool canPromotion() const;

    /**
     * 駒の所有者を取得
     *
     * @return Player
     */
    void setOwner(Player owner) { m_owner = owner; }

    /**
     * 駒の移動範囲を取得
     *
     * @return 移動範囲
     */
    MovingRangeList moveRanges() const;

    /**
     * 駒の位置
     *
     * @return 駒の位置
     */
    inline Point point() const { return m_point; }

    /**
     * 指定の座標を設定する
     *
     * @param point 座標
     */
    void setPoint(const Point &point);

    bool operator==(const Piece &);
    bool operator!=(const Piece &);
    QDataStream &operator <<(QDataStream &out);
    QDataStream &operator >>(QDataStream &in);

protected:

private:
    PieceInternal::Piece *internal;      ///< 内部駒情報
    Player m_owner;                 ///< 所有者
    Point m_point;                  ///< 配置座標
};

} // namespace Shogi

Q_DECLARE_METATYPE(Shogi::Piece)

#endif // SHOGI_PIECE_H
