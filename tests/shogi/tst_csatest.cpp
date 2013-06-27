#include <QtCore/QString>
#include <QtTest/QtTest>

#include <shogi/shogi.h>
#include <shogi/csa.h>
#include <shogi/board.h>
#include <shogi/piece.h>

using namespace Shogi;

class CsaTest : public QObject
{
    Q_OBJECT

public:
    CsaTest();

private Q_SLOTS:
    void sampleTest();
};

CsaTest::CsaTest()
{
}

void CsaTest::sampleTest()
{
    Csa csa("'----------棋譜ファイルの例\"example.csa\"-----------------\n"
            "'バージョン\n"
            "V2.2\n"
            "'対局者名\n"
            "N+NAKAHARA\n"
            "N-YONENAGA\n"
            "'棋譜情報\n"
            "'棋戦名\n"
            "$EVENT:13th World Computer Shogi Championship\n"
            "'対局場所\n"
            "$SITE:KAZUSA ARC\n"
            "'開始日時\n"
            "$START_TIME:2003/05/03 10:30:00\n"
            "'終了日時\n"
            "$END_TIME:2003/05/03 11:11:05\n"
            "'持ち時間:25分、切れ負け\n"
            "$TIME_LIMIT:00:25+00\n"
            "'戦型:矢倉\n"
            "$OPENING:YAGURA\n"
            "'平手の局面\n"
            "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n"
            "P2 * -HI *  *  *  *  * -KA * \n"
            "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n"
            "P4 *  *  *  *  *  *  *  *  * \n"
            "P5 *  *  *  *  *  *  *  *  * \n"
            "P6 *  *  *  *  *  *  *  *  * \n"
            "P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n"
            "P8 * +KA *  *  *  *  * +HI * \n"
            "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n"
            "'先手番\n"
            "+\n"
            "'指し手と消費時間\n"
            "+2726FU\n"
            "T12\n"
            "-3334FU\n"
            "T6\n"
            "%CHUDAN\n"
            "'---------------------------------------------------------\n");

    QCOMPARE(csa.toBoard().toCsaString(), String(
                 "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n"
                 "P2 * -HI *  *  *  *  * -KA * \n"
                 "P3-FU-FU-FU-FU-FU-FU * -FU-FU\n"
                 "P4 *  *  *  *  *  * -FU *  * \n"
                 "P5 *  *  *  *  *  *  *  *  * \n"
                 "P6 *  *  *  *  *  *  * +FU * \n"
                 "P7+FU+FU+FU+FU+FU+FU+FU * +FU\n"
                 "P8 * +KA *  *  *  *  * +HI * \n"
                 "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n"));
}

QTEST_APPLESS_MAIN(CsaTest);

#include "tst_csatest.moc"
