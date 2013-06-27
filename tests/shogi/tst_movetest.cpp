#include <QtCore/QString>
#include <QtTest/QtTest>

#include <shogi/shogi.h>
#include <shogi/csa.h>
#include <shogi/board.h>
#include <shogi/piece.h>
#include <shogi/move.h>

using namespace Shogi;

class MoveTest : public QObject
{
    Q_OBJECT

public:
    MoveTest();

private Q_SLOTS:
};

MoveTest::MoveTest()
{
}

QTEST_APPLESS_MAIN(MoveTest);

#include "tst_movetest.moc"
