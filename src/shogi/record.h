#ifndef SHOGI_RECORD_H
#define SHOGI_RECORD_H

#include "shogi.h"

namespace Shogi {

/**
 * 棋譜データ
 *
 * 棋譜の１手を記録するためのクラス
 */
class Record
{
public:
    Record();

    /**
     * @param turn 手番
     * @param from 駒座標
     * @param to 移動座標
     * @param piece_type 駒種別
     * @param sec 時間
     */
    Record(Player turn, const Point &from, const Point &to, PieceType piece_type, int sec = 0);

    /**
     * @param turn 手番
     * @param status ゲーム終了ステータス
     */
    Record(Player turn, GameStatus status);

    /**
     * ゲームステータスを取得する
     *
     * @return ゲーム終了の理由が返却される。
     *         継続中は NoEnd が返却される。
     */
    inline GameStatus status() const { return _status; }

    /**
     * 手番者を取得する
     *
     * @return 手番者
     */
    inline Player turn() const { return _turn; }

    /**
     * 駒の移動元座標を取得する
     *
     * @return 駒の移動元座標。 ゲームが終了している場合は(-1, -1)が返却される。
     */
    inline Point from() const { return _from; }

    /**
     * 駒の移動先の座標を取得する
     *
     * @return 駒の移動先座標。 ゲームが終了している場合は(-1, -1)が返却される。
     */
    inline Point to() const { return _to; }

    /**
     * 移動した駒種別を取得する
     *
     * @return 駒種別。 ゲームが終了している場合は Empty が返却される。
     */
    inline PieceType pieceType() const { return _piece_type; }

    /**
     * 考慮時間を取得する
     *
     * @return 考慮時間。 ゲームが終了している場合は -1 が返却される。
     */
    inline int sec() const { return _sec; }

    /**
     * 考慮時間を設定する
     *
     * @param s 考慮時間
     */
    inline void setSec(int s) { _sec = s; }

private:
    GameStatus _status;         ///< ゲームの状態
    Player _turn;               ///< 手番
    Point _from;                ///< 移動元の座標
    Point _to;                  ///< 移動先の座標
    PieceType _piece_type;      ///< 移動する駒の種別
    int _sec;                   ///< 考慮時間
};

} // namespace Shogi

#endif // SHOGI_RECORD_H
