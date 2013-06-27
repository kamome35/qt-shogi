#ifndef COMPUTERHUMAN_H
#define COMPUTERHUMAN_H

#include "human.h"

class ComputerHuman : public Human
{
    Q_OBJECT
public:
    explicit ComputerHuman(Shogi::Player player, QObject *parent = 0);

protected:
    void run();
    void doThinking();

signals:
    
public slots:
    virtual void selectionPoint(const Shogi::Point &point);

private:
    QThread *think;
    
};

#endif // COMPUTERHUMAN_H
