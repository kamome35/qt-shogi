#ifndef SHOGICOMPONENT_H
#define SHOGICOMPONENT_H

#include <QObject>
#include <QThread>

#include <shogi/shogi.h>

class ShogiComponent : public QThread
{
    Q_OBJECT
public:
    ShogiComponent(QObject *parent = 0);
    ~ShogiComponent();

public slots:
    bool movePiece(Shogi::Player turn, const Shogi::Point &from, const Shogi::Point &to, Shogi::PieceType piece_type);

signals:
    void gameStart();
    void gameEnd();
    void pieceMoved(const Shogi::Point &from, const Shogi::Point &to, Shogi::PieceType piece_type);
    void recordAdded(const Shogi::Record &shogi_recoerd);

protected:
    void run();

private:
    Shogi::Component *component;
};

#endif // SHOGICOMPONENT_H
