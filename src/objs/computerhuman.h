#ifndef OBJS_COMPUTERHUMAN_H
#define OBJS_COMPUTERHUMAN_H

#include "human.h"

class ComputerHuman : public Human
{
    Q_OBJECT
public:
    explicit ComputerHuman(Shogi::Player player, QObject *parent = 0);
    virtual void setShogiComponent(ShogiComponent *shogi_component);

protected:
    void run();

signals:
    
public slots:
    void startThinking();
    void doThinking();
    virtual void selectionPoint(const Shogi::Point &point);

private:
    QThread *think;
    
};

#endif // OBJS_COMPUTERHUMAN_H
