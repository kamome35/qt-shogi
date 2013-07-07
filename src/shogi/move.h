#ifndef SHOGI_MOVE_H
#define SHOGI_MOVE_H

#include "shogi.h"
#include "board.h"

namespace Shogi {

/**
 * 駒の移動を管理するクラス
 *
 * 移動可能な駒の取得、特定の駒の移動できる座標の取得や成り判定などの補助をする
 */
class Move
{
public:
    Move(const Board &board);

    /**
     * 駒の移動可能座標を取得する。
     *
     * @param piece
     * @return
     */
    MovePointList movePoints(const Piece &piece) const;

    /**
     * プレイヤーの移動可能な駒情報を取得する。
     *
     * @param player
     * @return
     */
    PieceList movablePieces(Player player) const;

    /**
     * 指定した座標に移動可能か判定する
     *
     * @param player
     * @param from (0, 0) ～ (9, 9)の範囲で移動元の座標を指定する。(0, 0)は持駒を示す
     * @param to (1, 1) ～ (9, 9)の範囲で移動先の座標を指定する。
     * @param piece_type 駒の種別
     * @return 移動可能であれば true を返却する。 移動できない場合はfalaeを返却する。
     */
    bool canMove(Player player, const Point &from, const Point &to, PieceType piece_type);

    /**
     * 移動時の成り判定
     *
     * @param piece 移動する駒
     * @param to 移動先の座標
     * @return 成れない場合は PromotionNone が返却され、
     *         成る事が出来る場合は PromotionAny が返却さる。
     *         また、成る必要がある場合は PromotionNeed が返却される。
     *         PromotionNeed は駒の移動先を動けない場所に指定した場合返却される。
     *         駒を移動できない場所に配置すると反則負けと成る。
     */
    MovePromotion movePromotionJudge(const Piece &piece, const Point &to) const;

protected:

    /**
     * 駒が盤上にある場合の移動可能座標を取得する。
     *
     * @param piece
     * @return 移動可能座標
     */
    MovePointList movePointsOfSquarePiece(const Piece &piece) const;

    /**
     * 駒が駒台にある場合の移動可能座標を取得する。
     *
     * @param piece
     * @return 移動可能座標
     */
    MovePointList movePointsOfHandPiece(const Piece &piece) const;

    /**
     * 駒の表側の種別を取得する
     *
     * @param piece_type
     * @return
     */
    PieceType frontPieceType(PieceType piece_type) const;

    /**
     * 駒の裏側の種別を取得する
     *
     * @param piece_type 検索したい駒種別を指定する
     * @return 指定した駒種別の裏側の種別を取得
     */
    PieceType reversePieceType(PieceType piece_type) const;

    /**
     * 王手状態チェック
     * 駒を移動した場合、自玉が王手状態にならないか判定する
     *
     * @param piece 移動する駒
     * @param to 移動先の座標
     * @return true が返却される場合は、駒を移動すると自玉が王手状態になる。 false が返却される場合は、王手状態にはならない。
     */
    bool kingDangerCheck(Piece piece, const Point &to) const;

    /**
     * ２歩チェック
     *
     * @param piece 配置する駒
     * @param x 捜査するX座標
     * @return 指定のX座標にすでに歩がある場合は true を返却する。 歩がない場合は false が返却される。
     *         また配置する駒が歩ではない場合は、２歩とはならないので必ず false が返却される。
     */
    bool doublePawnCheck(const Piece &piece, int x) const;

    /**
     * 打ち歩詰みチェック
     *
     * @param piece 配置する駒
     * @param to 配置する座標
     * @return 指定の座標に駒を配置した場合に打ち歩詰となる場合は true を返却する。 打ち歩詰とならない場合は false が返却される。
     */
    bool checkmatePawnCheck(Piece piece, const Point &to) const;

    /**
     * 配置チェック
     *
     * 駒を指定の座標に配置できるか確認する
     *
     * @param piece 配置する駒
     * @param to 配置座標
     * @return 配置先に駒が移動出来る場合は true を返却する。 移動できない場合は false を返却する。
     */
    bool placeCheck(const Piece &piece, const Point &to) const;

private:
    const Board &m_board;      ///< 盤面情報
};

} // namespace Shogi

#endif // SHOGI_MOVE_H
