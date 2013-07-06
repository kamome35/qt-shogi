#include "computerhuman.h"

using namespace Shogi;

ComputerHuman::ComputerHuman(Player player, QObject *parent) :
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

void ComputerHuman::selectionPoint(const Point &point)
{
    Q_UNUSED(point);
}
