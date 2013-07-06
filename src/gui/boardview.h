#ifndef GUI_BOARDVIEW_H
#define GUI_BOARDVIEW_H

#include <QGraphicsView>
#include <QGraphicsObject>

#include <shogi/shogi.h>

class SquareItem;

/**
 * 盤面描画
 *
 * 盤上を駒や持駒などを描画する
 */
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

/**
 *
 */
class SquareItem : public QGraphicsObject
{
    Q_OBJECT
public:
    SquareItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    inline void setPoint(const Shogi::Point &point) { m_point = point; }
    inline Shogi::Point point() const  { return m_point; }
    void setPiece(const Shogi::Piece *piece);
    void setNavi(bool enabled);
signals:
    void hoverPoint(const Shogi::Point &point);
    void clickPoint(const Shogi::Point &point);

public slots:
    void setClicked(bool enabled);

private:
    int m_uid;
    const Shogi::Piece *m_piece;
    Shogi::Point m_point;
    bool hover_enter;
    bool clicked;
    bool navi;
};

#endif // GUI_BOARDVIEW_H
