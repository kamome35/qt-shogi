#include "squareitem.h"
#include <QPainter>
#include <QPalette>
#include <QWidget>
#include <QGraphicsSceneHoverEvent>

#include "shogi/piece.h"

SquareItem::SquareItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_piece(0),
    m_point(-1, -1),
    hover_enter(false),
    clicked(false),
    navi(false)
{
    static int uid;
    m_uid = uid++;
    setAcceptHoverEvents(true);
}

QRectF SquareItem::boundingRect() const
{
    return QRectF(-25, -25, 50, 50);
}

void SquareItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);

    if (hover_enter) {
        painter->setBrush(widget->palette().brush(QPalette::Highlight));
    } else if (clicked) {
        painter->setBrush(Qt::darkCyan);
    } else if (navi) {
        painter->setBrush(Qt::lightGray);
    }
    painter->drawRect(boundingRect());

    if (m_piece) {
    }
}

void SquareItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (hover_enter != true) {
        hover_enter = true;
        update();

        emit hoverPoint(point());
    }
    event->accept();
}

void SquareItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (hover_enter != false) {
        hover_enter = false;
        update();
    }
    event->accept();
}

void SquareItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void SquareItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clickPoint(point());
    }
    event->accept();
}

void SquareItem::setPiece(const Shogi::Piece *piece)
{
    m_piece = piece;
    if (piece) {
        setRotation(piece->owner() == Shogi::Sente ? 0 : 180);
    }
    update();
}

void SquareItem::setNavi(bool enabled)
{
    if (navi != enabled) {
        navi = enabled;
        update();
    }
}

void SquareItem::setClicked(bool enabled)
{
    if (clicked != enabled) {
        clicked = enabled;
        update();
    }
}
