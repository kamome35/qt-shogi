#ifndef OBJS_HUMAN_H
#define OBJS_HUMAN_H

#include <QThread>
#include <shogi/shogi.h>

#include "shogicomponent.h"

/**
 * 指手管理オブジェクト
 *
 *
 */
class Human : public QThread
{
    Q_OBJECT
public:
    /**
     * 指手オブジェクトを生成する
     *
     * @param player 手番
     * @param parent 親オブジェクト
     */
    explicit Human(Shogi::Player player, QObject *parent = 0);
    virtual ~Human();

    void setShogiComponent(ShogiComponent *shogi_component);

protected:
    virtual void run();

signals:
    void selectPiece(const Shogi::Piece &piece);
    
public slots:
    /**
     * 座標の選択する
     *
     * 選択した座標に駒が自分の所有する駒が存在する場合は駒を選択する。
     * 選択した駒の移動可能な座標を選択した場合は選択中の駒を指定の座標に移動する。
     *
     * @param point 移動座標
     */
    virtual void selectionPoint(const Shogi::Point &point);
    
protected:
    /**
     * 駒の裏側の種別を取得する
     *
     * @param piece_type 検索したい駒種別を指定する
     * @return 指定した駒種別の裏側の種別を取得
     */
    Shogi::PieceType reversePieceType(Shogi::PieceType piece_type) const;

protected:
    Shogi::Component *component;
    Shogi::Player player;
    Shogi::MovePoint m_move_point;
    Shogi::Piece select_piece;
    bool thinking;
};

#endif // OBJS_HUMAN_H
