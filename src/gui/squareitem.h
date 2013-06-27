#ifndef SQUAREITEM_H
#define SQUAREITEM_H

#include <QGraphicsObject>
#include "shogi/shogi.h"

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


#endif // SQUAREITEM_H
