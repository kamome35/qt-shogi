#ifndef HUMAN_H
#define HUMAN_H

#include <QThread>
#include <shogi/shogi.h>
#include "shogicomponent.h"
#include <shogi/piece.h>

class Human : public QThread
{
    Q_OBJECT
public:
    explicit Human(Shogi::Player player, QObject *parent = 0);
    virtual ~Human();
    void setShogiComponent(ShogiComponent *shogi_component);

protected:
    virtual void run();

signals:
    void selectPiece(const Shogi::Piece &piece);
    
public slots:
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

#endif // HUMAN_H
