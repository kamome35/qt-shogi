#include <QString>
#include <QtTest>

#include "shogi/shogi.h"
#include "shogi/piece.h"

using namespace Shogi;

class PieceTest : public QObject
{
    Q_OBJECT
    
public:
    PieceTest();

private Q_SLOTS:
    void owner();
    void owner_data();
    void type();
    void type_data();
    void canPromotion();
    void canPromotion_data();
    void setPoint();
    void setPoint_data();
};

PieceTest::PieceTest()
{
}

void PieceTest::owner()
{
    QFETCH(Player, player);

    Piece pieceEmpty(player, PieceEmpty);
    Piece piecePawn(player, PiecePawn);
    Piece pieceLance(player, PieceLance);
    Piece pieceKnight(player, PieceKnight);
    Piece pieceSilver(player, PieceSilver);
    Piece pieceGold(player, PieceGold);
    Piece pieceRook(player, PieceRook);
    Piece pieceBishop(player, PieceBishop);
    Piece pieceKing(player, PieceKing);
    Piece piecePawnPromotion(player, PiecePawnPromotion);
    Piece pieceLancePromotion(player, PieceLancePromotion);
    Piece pieceKnightPromotion(player, PieceKnightPromotion);
    Piece pieceSilverPromotion(player, PieceSilverPromotion);
    Piece pieceRookPromotion(player, PieceRookPromotion);
    Piece pieceBishopPromotion(player, PieceBishopPromotion);

    QCOMPARE(pieceEmpty.owner(), player);
    QCOMPARE(piecePawn.owner(), player);
    QCOMPARE(pieceLance.owner(), player);
    QCOMPARE(pieceKnight.owner(), player);
    QCOMPARE(pieceSilver.owner(), player);
    QCOMPARE(pieceGold.owner(), player);
    QCOMPARE(pieceRook.owner(), player);
    QCOMPARE(pieceBishop.owner(), player);
    QCOMPARE(pieceKing.owner(), player);
    QCOMPARE(piecePawnPromotion.owner(), player);
    QCOMPARE(pieceLancePromotion.owner(), player);
    QCOMPARE(pieceKnightPromotion.owner(), player);
    QCOMPARE(pieceSilverPromotion.owner(), player);
    QCOMPARE(pieceRookPromotion.owner(), player);
    QCOMPARE(pieceBishopPromotion.owner(), player);
}

void PieceTest::owner_data()
{
    QTest::addColumn<Player>("player");

    // プレイヤー種別
    QTest::newRow("Sente") << Sente;
    QTest::newRow("Gote") << Gote;
}

void PieceTest::type()
{
    QFETCH(PieceType, piece_type);

    // 先手と後手で同種の駒を生成
    Piece sente_piece(Sente, piece_type);
    Piece gote_piece(Gote, piece_type);

    // 駒種別が正しいか確認
    QCOMPARE(sente_piece.type(), piece_type);
    QCOMPARE(gote_piece.type(), piece_type);
}

void PieceTest::type_data()
{
    QTest::addColumn<PieceType>("piece_type");

    // 全ての駒種別データ
    QTest::newRow("PieceEmpty")           << PieceEmpty;
    QTest::newRow("PiecePawn")            << PiecePawn;
    QTest::newRow("PieceLance")           << PieceLance;
    QTest::newRow("PieceKnight")          << PieceKnight;
    QTest::newRow("PieceSilver")          << PieceSilver;
    QTest::newRow("PieceGold")            << PieceGold;
    QTest::newRow("PieceRook")            << PieceRook;
    QTest::newRow("PieceBishop")          << PieceBishop;
    QTest::newRow("PieceKing")            << PieceKing;
    QTest::newRow("PiecePawnPromotion")   << PiecePawnPromotion;
    QTest::newRow("PieceLancePromotion")  << PieceLancePromotion;
    QTest::newRow("PieceKnightPromotion") << PieceKnightPromotion;
    QTest::newRow("PieceSilverPromotion") << PieceSilverPromotion;
    QTest::newRow("PieceRookPromotion")   << PieceRookPromotion;
    QTest::newRow("PieceBishopPromotion") << PieceBishopPromotion;
}

void PieceTest::canPromotion()
{
    QFETCH(Player, player);

    // 昇格のできる駒か
    QCOMPARE(Piece(player, PieceEmpty).canPromotion(), false);
    QCOMPARE(Piece(player, PiecePawn).canPromotion(), true);
    QCOMPARE(Piece(player, PieceLance).canPromotion(), true);
    QCOMPARE(Piece(player, PieceKnight).canPromotion(), true);
    QCOMPARE(Piece(player, PieceSilver).canPromotion(), true);
    QCOMPARE(Piece(player, PieceGold).canPromotion(), false);
    QCOMPARE(Piece(player, PieceRook).canPromotion(), true);
    QCOMPARE(Piece(player, PieceBishop).canPromotion(), true);
    QCOMPARE(Piece(player, PieceKing).canPromotion(), false);
    QCOMPARE(Piece(player, PiecePawnPromotion).canPromotion(), false);
    QCOMPARE(Piece(player, PieceLancePromotion).canPromotion(), false);
    QCOMPARE(Piece(player, PieceKnightPromotion).canPromotion(), false);
    QCOMPARE(Piece(player, PieceSilverPromotion).canPromotion(), false);
    QCOMPARE(Piece(player, PieceRookPromotion).canPromotion(), false);
    QCOMPARE(Piece(player, PieceBishopPromotion).canPromotion(), false);
}

void PieceTest::canPromotion_data()
{
    QTest::addColumn<Player>("player");

    // プレイヤー種別
    QTest::newRow("Sente") << Sente;
    QTest::newRow("Gote") << Gote;
}

void PieceTest::setPoint()
{
    QFETCH(Point, point);

    Piece piece(NoPlayer, PieceEmpty);

    piece.setPoint(point);
    QCOMPARE(piece.point(), point);
}

void PieceTest::setPoint_data()
{
    QTest::addColumn<Point>("point");

    QTest::newRow("0, 0") << Point(0, 0);
    QTest::newRow("0, 1") << Point(0, 1);
    QTest::newRow("0, 2") << Point(0, 2);
    QTest::newRow("0, 3") << Point(0, 3);
    QTest::newRow("0, 4") << Point(0, 4);
    QTest::newRow("0, 5") << Point(0, 5);
    QTest::newRow("0, 6") << Point(0, 6);
    QTest::newRow("0, 7") << Point(0, 7);
    QTest::newRow("0, 8") << Point(0, 8);
    QTest::newRow("0, 9") << Point(0, 9);
    QTest::newRow("1, 0") << Point(1, 0);
    QTest::newRow("1, 1") << Point(1, 1);
    QTest::newRow("1, 2") << Point(1, 2);
    QTest::newRow("1, 3") << Point(1, 3);
    QTest::newRow("1, 4") << Point(1, 4);
    QTest::newRow("1, 5") << Point(1, 5);
    QTest::newRow("1, 6") << Point(1, 6);
    QTest::newRow("1, 7") << Point(1, 7);
    QTest::newRow("1, 8") << Point(1, 8);
    QTest::newRow("1, 9") << Point(1, 9);
    QTest::newRow("2, 0") << Point(2, 0);
    QTest::newRow("2, 1") << Point(2, 1);
    QTest::newRow("2, 2") << Point(2, 2);
    QTest::newRow("2, 3") << Point(2, 3);
    QTest::newRow("2, 4") << Point(2, 4);
    QTest::newRow("2, 5") << Point(2, 5);
    QTest::newRow("2, 6") << Point(2, 6);
    QTest::newRow("2, 7") << Point(2, 7);
    QTest::newRow("2, 8") << Point(2, 8);
    QTest::newRow("2, 9") << Point(2, 9);
    QTest::newRow("3, 0") << Point(3, 0);
    QTest::newRow("3, 1") << Point(3, 1);
    QTest::newRow("3, 2") << Point(3, 2);
    QTest::newRow("3, 3") << Point(3, 3);
    QTest::newRow("3, 4") << Point(3, 4);
    QTest::newRow("3, 5") << Point(3, 5);
    QTest::newRow("3, 6") << Point(3, 6);
    QTest::newRow("3, 7") << Point(3, 7);
    QTest::newRow("3, 8") << Point(3, 8);
    QTest::newRow("3, 9") << Point(3, 9);
    QTest::newRow("4, 0") << Point(4, 0);
    QTest::newRow("4, 1") << Point(4, 1);
    QTest::newRow("4, 2") << Point(4, 2);
    QTest::newRow("4, 3") << Point(4, 3);
    QTest::newRow("4, 4") << Point(4, 4);
    QTest::newRow("4, 5") << Point(4, 5);
    QTest::newRow("4, 6") << Point(4, 6);
    QTest::newRow("4, 7") << Point(4, 7);
    QTest::newRow("4, 8") << Point(4, 8);
    QTest::newRow("4, 9") << Point(4, 9);
    QTest::newRow("5, 0") << Point(5, 0);
    QTest::newRow("5, 1") << Point(5, 1);
    QTest::newRow("5, 2") << Point(5, 2);
    QTest::newRow("5, 3") << Point(5, 3);
    QTest::newRow("5, 4") << Point(5, 4);
    QTest::newRow("5, 5") << Point(5, 5);
    QTest::newRow("5, 6") << Point(5, 6);
    QTest::newRow("5, 7") << Point(5, 7);
    QTest::newRow("5, 8") << Point(5, 8);
    QTest::newRow("5, 9") << Point(5, 9);
    QTest::newRow("6, 0") << Point(6, 0);
    QTest::newRow("6, 1") << Point(6, 1);
    QTest::newRow("6, 2") << Point(6, 2);
    QTest::newRow("6, 3") << Point(6, 3);
    QTest::newRow("6, 4") << Point(6, 4);
    QTest::newRow("6, 5") << Point(6, 5);
    QTest::newRow("6, 6") << Point(6, 6);
    QTest::newRow("6, 7") << Point(6, 7);
    QTest::newRow("6, 8") << Point(6, 8);
    QTest::newRow("6, 9") << Point(6, 9);
    QTest::newRow("7, 0") << Point(7, 0);
    QTest::newRow("7, 1") << Point(7, 1);
    QTest::newRow("7, 2") << Point(7, 2);
    QTest::newRow("7, 3") << Point(7, 3);
    QTest::newRow("7, 4") << Point(7, 4);
    QTest::newRow("7, 5") << Point(7, 5);
    QTest::newRow("7, 6") << Point(7, 6);
    QTest::newRow("7, 7") << Point(7, 7);
    QTest::newRow("7, 8") << Point(7, 8);
    QTest::newRow("7, 9") << Point(7, 9);
    QTest::newRow("8, 0") << Point(8, 0);
    QTest::newRow("8, 1") << Point(8, 1);
    QTest::newRow("8, 2") << Point(8, 2);
    QTest::newRow("8, 3") << Point(8, 3);
    QTest::newRow("8, 4") << Point(8, 4);
    QTest::newRow("8, 5") << Point(8, 5);
    QTest::newRow("8, 6") << Point(8, 6);
    QTest::newRow("8, 7") << Point(8, 7);
    QTest::newRow("8, 8") << Point(8, 8);
    QTest::newRow("8, 9") << Point(8, 9);
    QTest::newRow("9, 0") << Point(9, 0);
    QTest::newRow("9, 1") << Point(9, 1);
    QTest::newRow("9, 2") << Point(9, 2);
    QTest::newRow("9, 3") << Point(9, 3);
    QTest::newRow("9, 4") << Point(9, 4);
    QTest::newRow("9, 5") << Point(9, 5);
    QTest::newRow("9, 6") << Point(9, 6);
    QTest::newRow("9, 7") << Point(9, 7);
    QTest::newRow("9, 8") << Point(9, 8);
    QTest::newRow("9, 9") << Point(9, 9);
}


QTEST_APPLESS_MAIN(PieceTest)

#include "tst_piecetest.moc"
