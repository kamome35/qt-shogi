#include "boardview.h"
#include <QGraphicsSceneHoverEvent>

#include <shogi/shogi.h>
#include <shogi/piece.h>
#include <shogi/component.h>
#include <shogi/move.h>

using namespace Shogi;

const char *x_num[] = { "１", "２", "３", "４", "５", "６", "７", "８", "９" };
const char *y_num[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
const char *piece_name[] = { "", "歩", "香", "桂", "銀", "金", "飛", "角", "玉", "と", "杏", "圭", "全", "竜", "馬" };


namespace BoardViewInner {

SquareItem::SquareItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_piece(),
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

    painter->drawText(boundingRect(), Qt::AlignCenter, tr(piece_name[m_piece.type()]));
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

void SquareItem::setPiece(const Piece &piece)
{
    m_piece = piece;
    setRotation(piece.owner() == Sente ? 0 : 180);
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

class SquareTextItem : public QGraphicsItem
{
public:
    SquareTextItem(const QString &text, QGraphicsItem *parent = 0) :
        QGraphicsItem(parent),
        text(text)
    {
    }

    QRectF boundingRect() const
    {
        return QRectF(-6, -6, 12, 12);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignCenter, text);
    }

private:
    QString text;
    QFont font;
};

} // namespace BoardViewInner

BoardView::BoardView(QWidget *parent) :
    QGraphicsView(parent),
    select_point(-1, -1),
    selectSquare(NULL)
{
    QGraphicsScene *scene = new QGraphicsScene(this);

    // 盤
    const int board_offs = SquareWidth / 5;
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        BoardViewInner::SquareTextItem *item = new BoardViewInner::SquareTextItem(tr(x_num[x-1]));
        item->setPos((BOARD_X_MAX - x) * SquareWidth, board_offs);
        scene->addItem(item);
    }
    for (int y = 1; y <= BOARD_Y_MAX; ++y) {
        BoardViewInner::SquareTextItem *item = new BoardViewInner::SquareTextItem(tr(y_num[y-1]));
        item->setPos(BOARD_X_MAX * SquareWidth - board_offs, y * SquareWidth);
        scene->addItem(item);
    }
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        for (int y = 1; y <= BOARD_Y_MAX; ++y) {
            BoardViewInner::SquareItem *item = new BoardViewInner::SquareItem();
            board[x - 1][y - 1] = item;
            item->setPos((BOARD_X_MAX - x) * SquareWidth, y * SquareWidth);
            item->setPoint(Point(x, y));
            scene->addItem(item);
            connect(item, SIGNAL(clickPoint(Shogi::Point)), this, SLOT(selectionBoardPoint(Shogi::Point)));
        }
    }

    /* 持ち駒台 */
    // 先手
    for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
        BoardViewInner::SquareItem *item = new BoardViewInner::SquareItem();
        handBoard[Sente][i] = item;
        item->setPos(BOARD_X_MAX * SquareWidth + SquareWidth, (i + 3) * SquareWidth);
        item->setPoint(Point(0, i));
        scene->addItem(item);
        connect(item, SIGNAL(clickPoint(Shogi::Point)), this, SLOT(selectionSenteHandPoint(Shogi::Point)));
    }
    // 後手
    for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
        BoardViewInner::SquareItem *item = new BoardViewInner::SquareItem();
        handBoard[Gote][i] = item;
        item->setPos(-SquareWidth * 2, BOARD_Y_MAX * SquareWidth - SquareWidth * (i + 2));
        item->setPoint(Point(0, i));
        scene->addItem(item);
        connect(item, SIGNAL(clickPoint(Shogi::Point)), this, SLOT(selectionGoteHandPoint(Shogi::Point)));
    }
    setScene(scene);
}

BoardView::~BoardView()
{
    for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
        delete handBoard[Gote][i];
        delete handBoard[Sente][i];
    }
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        for (int y = 1; y <= BOARD_Y_MAX; ++y) {
            delete board[x - 1][y - 1];
        }
    }
}

void BoardView::setShogiComponent(const Component *component)
{
    shogiComonent = component;
    boardUpdate();
}

void BoardView::selectionBoardPoint(const Point &point)
{
    qDebug("x=%d, y=%d", point.x(), point.y());
    select_point = point;

    if (selectSquare) selectSquare->setClicked(false);
    selectSquare = board[point.x() - 1][point.y() - 1];
    if (selectSquare) selectSquare->setClicked(true);

    naviClear();

    emit selectedBoardPoint(point);
}

void BoardView::selectionSenteHandPoint(const Point &point)
{
    qDebug("y=%d", point.y());
    select_point = point;

    if (selectSquare) selectSquare->setClicked(false);
    selectSquare = handBoard[Sente][point.y()];
    if (selectSquare) selectSquare->setClicked(true);

    naviClear();

    emit selectedSenteHandPoint(point);
}

void BoardView::selectionGoteHandPoint(const Point &point)
{
    qDebug("y=%d", point.y());
    select_point = point;

    if (selectSquare) selectSquare->setClicked(false);
    selectSquare = handBoard[Gote][point.y()];
    if (selectSquare) selectSquare->setClicked(true);

    naviClear();

    emit selectedGoteHandPoint(point);
}

void BoardView::selectedPiece(const Piece &piece)
{
    MovePointList move_points = Move(shogiComonent->board()).movePoints(piece);
    foreach (const MovePoint &move_point, move_points) {
        board[move_point.to.x() - 1][move_point.to.y() - 1]->setNavi(true);
    }
}

void BoardView::boardUpdate(const Point &from, const Point &to, PieceType piece_type)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    Q_UNUSED(piece_type);
    boardUpdate();
}

void BoardView::boardUpdate() const
{
    const Board b = shogiComonent->board();
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        for (int y = 1; y <= BOARD_Y_MAX; ++y) {
            Piece piece = b.squarePiece(Point(x, y));
            board[x - 1][y - 1]->setPiece(piece);
        }
    }
    for (int i = 1; i <= HAND_PIECE_TYPE_NUM; ++i) {
        const PieceList &piece_list = b.handPieces(Sente, static_cast<PieceType>(i));
        if (piece_list.count() > 0) {
            handBoard[Sente][i - 1]->setPiece(piece_list.first());
        }
    }
    for (int i = 1; i <= HAND_PIECE_TYPE_NUM; ++i) {
        const PieceList &piece_list = b.handPieces(Gote, static_cast<PieceType>(i));
        if (piece_list.count() > 0) {
            handBoard[Gote][i - 1]->setPiece(piece_list.first());
        }
    }
}

void BoardView::naviClear() const
{
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        for (int y = 1; y <= BOARD_Y_MAX; ++y) {
            board[x - 1][y - 1]->setNavi(false);
        }
    }
}
