#include <QtCore/QString>
#include <QtTest/QtTest>

#include "shogi/shogi.h"
#include "shogi/board.h"
#include "shogi/csa.h"

using namespace Shogi;

struct PieceInitList {
    Player owner;
    PieceType piece_type;
    Point point;
};

// 平手の駒配置
const static PieceInitList piece_init_type[] = {
    { Sente, PiecePawn,   Point(1, 7) },
    { Sente, PiecePawn,   Point(2, 7) },
    { Sente, PiecePawn,   Point(3, 7) },
    { Sente, PiecePawn,   Point(4, 7) },
    { Sente, PiecePawn,   Point(5, 7) },
    { Sente, PiecePawn,   Point(6, 7) },
    { Sente, PiecePawn,   Point(7, 7) },
    { Sente, PiecePawn,   Point(8, 7) },
    { Sente, PiecePawn,   Point(9, 7) },
    { Sente, PieceRook,   Point(2, 8) },
    { Sente, PieceBishop, Point(8, 8) },
    { Sente, PieceLance,  Point(1, 9) },
    { Sente, PieceKnight, Point(2, 9) },
    { Sente, PieceSilver, Point(3, 9) },
    { Sente, PieceGold,   Point(4, 9) },
    { Sente, PieceKing,   Point(5, 9) },
    { Sente, PieceGold,   Point(6, 9) },
    { Sente, PieceSilver, Point(7, 9) },
    { Sente, PieceKnight, Point(8, 9) },
    { Sente, PieceLance,  Point(9, 9) },
    { Gote,  PiecePawn,   Point(1, 3) },
    { Gote,  PiecePawn,   Point(2, 3) },
    { Gote,  PiecePawn,   Point(3, 3) },
    { Gote,  PiecePawn,   Point(4, 3) },
    { Gote,  PiecePawn,   Point(5, 3) },
    { Gote,  PiecePawn,   Point(6, 3) },
    { Gote,  PiecePawn,   Point(7, 3) },
    { Gote,  PiecePawn,   Point(8, 3) },
    { Gote,  PiecePawn,   Point(9, 3) },
    { Gote,  PieceRook,   Point(8, 2) },
    { Gote,  PieceBishop, Point(2, 2) },
    { Gote,  PieceLance,  Point(1, 1) },
    { Gote,  PieceKnight, Point(2, 1) },
    { Gote,  PieceSilver, Point(3, 1) },
    { Gote,  PieceGold,   Point(4, 1) },
    { Gote,  PieceKing,   Point(5, 1) },
    { Gote,  PieceGold,   Point(6, 1) },
    { Gote,  PieceSilver, Point(7, 1) },
    { Gote,  PieceKnight, Point(8, 1) },
    { Gote,  PieceLance,  Point(9, 1) },
};

class BoardTest : public QObject
{
    Q_OBJECT

public:
    BoardTest();

private Q_SLOTS:
    void toCsaString();
    void movePiece();
    void outeCheck();
    void checkmateCheck();
};

BoardTest::BoardTest()
{
}

void BoardTest::toCsaString()
{
    Board board;

    // 平手で駒を登録する
    const int count = sizeof(piece_init_type) / sizeof(piece_init_type[0]);
    for (int i = 0; i < count; ++i) {
        Piece piece(piece_init_type[i].owner, piece_init_type[i].piece_type);
        piece.setPoint(piece_init_type[i].point);
        board.setPiece(piece);
    }

    QCOMPARE(board.toCsaString(), String(
                 "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n"
                 "P2 * -HI *  *  *  *  * -KA * \n"
                 "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n"
                 "P4 *  *  *  *  *  *  *  *  * \n"
                 "P5 *  *  *  *  *  *  *  *  * \n"
                 "P6 *  *  *  *  *  *  *  *  * \n"
                 "P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n"
                 "P8 * +KA *  *  *  *  * +HI * \n"
                 "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n"));
}

void BoardTest::movePiece()
{
    Board board;

    // 平手で駒を登録する
    const int count = sizeof(piece_init_type) / sizeof(piece_init_type[0]);
    for (int i = 0; i < count; ++i) {
        Piece piece(piece_init_type[i].owner, piece_init_type[i].piece_type);
        piece.setPoint(piece_init_type[i].point);
        board.setPiece(piece);
    }

    const Piece &piece = board.squarePiece(Point(8, 7));

    board.movePiece(piece, Point(8, 6));

    QCOMPARE(board.toCsaString(), String(
                 "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n"
                 "P2 * -HI *  *  *  *  * -KA * \n"
                 "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n"
                 "P4 *  *  *  *  *  *  *  *  * \n"
                 "P5 *  *  *  *  *  *  *  *  * \n"
                 "P6 * +FU *  *  *  *  *  *  * \n"
                 "P7+FU * +FU+FU+FU+FU+FU+FU+FU\n"
                 "P8 * +KA *  *  *  *  * +HI * \n"
                 "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n"));
}

void BoardTest::outeCheck()
{
    const PieceInitList sente_checkmate[] = {
        { Sente, PieceGold, Point(5, 2) },
        { Gote,  PieceKing, Point(5, 1) }
    };
    Board sente_board;

    for (int i = 0; i < sizeof(sente_checkmate) / sizeof(piece_init_type[0]); ++i) {
        Piece piece(sente_checkmate[i].owner, sente_checkmate[i].piece_type);
        piece.setPoint(sente_checkmate[i].point);
        sente_board.setPiece(piece);
    }
    QVERIFY(!sente_board.outeCheck(Sente));
    QVERIFY(sente_board.outeCheck(Gote));

    const PieceInitList gote_checkmate[] = {
        { Gote,  PiecePawn, Point(5, 7) },
        { Gote,  PieceGold, Point(5, 8) },
        { Sente, PieceKing, Point(5, 9) }
    };
    Board gote_board;

    for (int i = 0; i < sizeof(gote_checkmate) / sizeof(piece_init_type[0]); ++i) {
        Piece piece(gote_checkmate[i].owner, gote_checkmate[i].piece_type);
        piece.setPoint(gote_checkmate[i].point);
        gote_board.setPiece(piece);
    }
    QVERIFY(gote_board.outeCheck(Sente));
    QVERIFY(!gote_board.outeCheck(Gote));
}

void BoardTest::checkmateCheck()
{
    const PieceInitList sente_checkmate[] = {
        { Sente, PiecePawn, Point(5, 3) },
        { Sente, PieceGold, Point(5, 2) },
        { Gote,  PieceKing, Point(5, 1) }
    };
    Board sente_board;

    for (int i = 0; i < sizeof(sente_checkmate) / sizeof(piece_init_type[0]); ++i) {
        Piece piece(sente_checkmate[i].owner, sente_checkmate[i].piece_type);
        piece.setPoint(sente_checkmate[i].point);
        sente_board.setPiece(piece);
    }
    QVERIFY(!sente_board.checkmateCheck(Sente));
    QVERIFY(sente_board.checkmateCheck(Gote));

    const PieceInitList gote_checkmate[] = {
        { Gote,  PiecePawn, Point(5, 7) },
        { Gote,  PieceGold, Point(5, 8) },
        { Sente, PieceKing, Point(5, 9) }
    };
    Board gote_board;

    for (int i = 0; i < sizeof(gote_checkmate) / sizeof(piece_init_type[0]); ++i) {
        Piece piece(gote_checkmate[i].owner, gote_checkmate[i].piece_type);
        piece.setPoint(gote_checkmate[i].point);
        gote_board.setPiece(piece);
    }
    QVERIFY(gote_board.checkmateCheck(Sente));
    QVERIFY(!gote_board.checkmateCheck(Gote));
}

QTEST_APPLESS_MAIN(BoardTest);

#include "tst_boardtest.moc"
