#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>
#include "shogi/component.h"
#include "shogi/shogi.h"
#include "squareitem.h"

class BoardView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = 0);
    virtual ~BoardView();
    void setShogiComponent(const Shogi::Component *component);
    void naviClear() const;
    void boardUpdate() const;
signals:
    void selectedBoardPoint(const Shogi::Point &point);
    void selectedSenteHandPoint(const Shogi::Point &point);
    void selectedGoteHandPoint(const Shogi::Point &point);
    
public slots:
    void selectionBoardPoint(const Shogi::Point &point);
    void selectionSenteHandPoint(const Shogi::Point &point);
    void selectionGoteHandPoint(const Shogi::Point &point);
    void selectedPiece(const Shogi::Piece *piece);
    void boardUpdate(const Shogi::Point &from, const Shogi::Point &to, Shogi::PieceType piece_type);

private:
    static const int SquareWidth = 50;
    const Shogi::Component *shogiComonent;
    SquareItem *board[Shogi::BOARD_X_MAX][Shogi::BOARD_Y_MAX];
    SquareItem *handBoard[Shogi::PLAYER_MAX][Shogi::HAND_PIECE_TYPE_NUM];
    Shogi::Point select_point;
    SquareItem *selectSquare;
};

#endif // BOARDVIEW_H
