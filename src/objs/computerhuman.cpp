#include "computerhuman.h"

ComputerHuman::ComputerHuman(Shogi::Player player, QObject *parent) :
    Human(player, parent)
{
    think = new QThread();

    connect(think, SIGNAL(started()), this, SLOT(doThinking()));
}

void ComputerHuman::run()
{
}

void ComputerHuman::doThinking()
{
}

void ComputerHuman::selectionPoint(const Shogi::Point &point)
{
    Q_UNUSED(point);
}
