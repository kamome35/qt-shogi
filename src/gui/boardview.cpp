#include "boardview.h"

#include "shogi/board.h"
#include "shogi/move.h"

using namespace Shogi;

const char *x_num[] = { "１", "２", "３", "４", "５", "６", "７", "８", "９" };
const char *y_num[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

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

BoardView::BoardView(QWidget *parent) :
    QGraphicsView(parent),
    select_point(-1, -1),
    selectSquare(NULL)
{
    QGraphicsScene *scene = new QGraphicsScene(this);

    // 盤
    const int board_offs = SquareWidth / 5;
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        SquareTextItem *item = new SquareTextItem(tr(x_num[x-1]));
        item->setPos((BOARD_X_MAX - x) * SquareWidth, board_offs);
        scene->addItem(item);
    }
    for (int y = 1; y <= BOARD_Y_MAX; ++y) {
        SquareTextItem *item = new SquareTextItem(tr(y_num[y-1]));
        item->setPos(BOARD_X_MAX * SquareWidth - board_offs, y * SquareWidth);
        scene->addItem(item);
    }
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        for (int y = 1; y <= BOARD_Y_MAX; ++y) {
            SquareItem *item = new SquareItem();
            board[x - 1][y - 1] = item;
            item->setPos((BOARD_X_MAX - x) * SquareWidth, y * SquareWidth);
            item->setPoint(Shogi::Point(x, y));
            scene->addItem(item);
            //connect(item, SIGNAL(hoverPoint(Shogi::Point)), this, SIGNAL(hoverPoint(Shogi::Point)));
            connect(item, SIGNAL(clickPoint(Shogi::Point)), this, SLOT(selectionBoardPoint(Shogi::Point)));
        }
    }

    /* 持ち駒台 */
    // 先手
    for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
        SquareItem *item = new SquareItem();
        handBoard[Sente][i] = item;
        item->setPos(BOARD_X_MAX * SquareWidth + SquareWidth, (i + 3) * SquareWidth);
        item->setPoint(Shogi::Point(0, i));
        scene->addItem(item);
        //connect(item, SIGNAL(hoverPoint(Shogi::Point)), this, SIGNAL(hoverPoint(Shogi::Point)));
        connect(item, SIGNAL(clickPoint(Shogi::Point)), this, SLOT(selectionSenteHandPoint(Shogi::Point)));
    }
    // 後手
    for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
        SquareItem *item = new SquareItem();
        handBoard[Gote][i] = item;
        item->setPos(-SquareWidth * 2, BOARD_Y_MAX * SquareWidth - SquareWidth * (i + 2));
        item->setPoint(Shogi::Point(0, i));
        scene->addItem(item);
        //connect(item, SIGNAL(hoverPoint(Shogi::Point)), this, SIGNAL(hoverPoint(Shogi::Point)));
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

void BoardView::boardUpdate() const
{
}

void BoardView::naviClear() const
{
    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        for (int y = 1; y <= BOARD_Y_MAX; ++y) {
            board[x - 1][y - 1]->setNavi(false);
        }
    }
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

void BoardView::selectedPiece(const Piece *piece)
{
}

void BoardView::boardUpdate(const Point &from, const Point &to, PieceType piece_type)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    Q_UNUSED(piece_type);
    boardUpdate();
}
