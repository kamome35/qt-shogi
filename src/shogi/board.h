#ifndef SHOGI_BOARD_H
#define SHOGI_BOARD_H

#include "shogi.h"
#include "piece.h"

namespace Shogi {

/**
 * 盤上の駒や持駒などの状態を管理するクラス
 */
class Board
{
public:
    Board();
    virtual ~Board();

    /**
     * piece に指定した駒を盤に登録する。
     *
     * @param piece
     */
    void setPiece(Piece &piece);

    /**
     * piece に指定した駒を盤面から削除する。
     *
     * @param piece
     */
    void removePiece(Piece &piece);

    /**
     * 駒を移動する
     * to は盤面上の(1, 1)～(9, 9)の範囲で指定する
     *
     * @param piece 移動元の駒
     * @param to 移動先
     */
    void movePiece(Piece piece, const Point &to);

    /**
     * Move クラスを呼び出す
     *
     * @return Moveクラスオブジェクト
     */
    Move move() const;

    /**
     * 盤面に存在するすべての駒を取得する
     *
     * @return 駒リスト
     */
    PieceList pieces() const;

    /**
     * 特定座標の駒を取得
     *
     * @param player プレイヤー
     * @param from 駒を取得する座標
     * @param piece_type 対象の駒
     * @return 存在する駒を取得する。 駒が存在しない場合は PieceEmpty が返却される。
     */
    Piece piece(Player player, const Point &from, PieceType piece_type) const;

    /**
     * プレイヤーの所持する駒をすべて取得する。
     *
     * @param player プレイヤー
     * @return player の所持する駒リスト
     */
    PieceList playerPieces(Player player) const;

    /**
     * 盤上の駒を取得する。
     * pointには(1, 1)~(9, 9)の範囲で指定する
     *
     * @param point 駒の位置
     * @return point に指定した座標に存在する駒を取得する。駒がない場合はNULLを返却する。
     */
    Piece squarePiece(const Point &point) const;

    /**
     * 持駒を取得する。
     *
     * @param player プレイヤー
     * @param piece_type 駒種別
     * @return piece_type に指定した種別の駒を取得する。
     * piece_typeに指定した駒をplayerｇが所持していない場合はNULLを返却する。
     */
    PieceList handPieces(Player player, PieceType piece_type) const;

    /**
     * プレイヤーの玉駒情報を取得する。
     *
     * @param player プレイヤー
     * @return player の玉の駒を取得する
     */
    Piece kingPiece(Player player) const;

    /**
     * 王手判定を実施する
     *
     * @param player 判定する対象のプレイヤー
     * @return true が返却される場合は、プレイヤーは王手されている状態、false が返却される場合は王手されていない。
     */
    bool outeCheck(Player player) const;

    /**
     * 詰み判定を実施する
     *
     * @param player 判定する対象のプレイヤー
     * @return true が返却される場合は、プレイヤーは 詰み状態、false が返却される場合は 詰みではいない。
     */
    bool checkmateCheck(Player player) const;

    /**
     * 盤面情報をCSA形式に変換する
     *
     * @return CSA文字列
     */
    String toCsaString() const;

protected:
    /**
     * 駒の表側の種別を取得する
     * @param piece_type 検索したい駒種別を指定する
     * @return 指定した駒種別の表側の種別を取得
     */
    PieceType frontsidePieceType(PieceType piece_type);

private:
    PieceList m_pieces;                                     /**< すべての駒情報 */
    PieceList player_pieces[PLAYER_MAX];                    /**< プレイヤーの駒 */
    HandPieceMap hand_piece[PLAYER_MAX];                    /**< 持駒 */
    Piece square_piece[BOARD_X_MAX][BOARD_Y_MAX];           /**< 盤上の駒 */
    Piece king_piece[PLAYER_MAX];                           /**< 玉駒 */
};

} // namespace Shogi

#endif // SHOGI_BOARD_H
