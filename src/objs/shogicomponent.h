#ifndef OBJS_SHOGICOMPONENT_H
#define OBJS_SHOGICOMPONENT_H

#include <QObject>
#include <QThread>

#include <shogi/shogi.h>
#include <shogi/component.h>

/**
 * 将棋コンポーネント
 *
 * 将棋の進行および指手の正当性などを評価する。
 * ゲーム開始時間
 */
class ShogiComponent : public QThread, public Shogi::Component
{
    Q_OBJECT
public:
    ShogiComponent(QObject *parent = 0);
    ~ShogiComponent();

public slots:
    /**
     * 駒を移動する
     *
     * @param player 手番
     * @param from 移動元
     * @param to 移動先
     * @param piece_type 移動する駒種別
     * @return 駒を移動できた場合は true を返却する。 駒を移動できなかった場合は false を返却する。
     */
    bool movePiece(Shogi::Player turn, const Shogi::Point &from, const Shogi::Point &to, Shogi::PieceType piece_type);

signals:
    /**
     * ゲーム開始時に出力される
     */
    void gameStart();

    /**
     * ゲーム終了時に出力される
     */
    void gameEnd();

    /**
     * 駒の移動を検出した時に出力される
     *
     * @param from 移動元座標
     * @param to 移動先座標
     * @param piece_type 移動した駒種別
     */
    void pieceMoved(const Shogi::Point &from, const Shogi::Point &to, Shogi::PieceType piece_type);

    /**
     * 棋譜データを追加された時に出力される
     *
     * @param shogi_recoerd
     */
    void recordAdded(const Shogi::Record &shogi_recoerd);

protected:
    void run();
};

#endif // OBJS_SHOGICOMPONENT_H
