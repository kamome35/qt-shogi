#ifndef GUI_INFORMATION_H
#define GUI_INFORMATION_H

#include <QDockWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include <shogi/shogi.h>
#include <objs/shogicomponent.h>

class Information : public QDockWidget
{
    Q_OBJECT
public:
    explicit Information(QWidget *parent = 0);

    /**
     *
     * @param component
     */
    void setShogiComponent(const ShogiComponent *component);

signals:

public slots:
    void updateNowDateTime();
    void setStartDateTime();
    void setEndDateTime();
    void setGameStatusItem();
    void setGameStatusItem(Shogi::GameStatus game_status);
    void updateTimeLimit();
    void changedTurn();

private:
    const Shogi::Component *shogiComonent;
    QTimer *timer;
    QTime sec_counter;
    int senteTimeLimit;
    int goteTimeLimit;
    QListWidget *widget;
    QListWidgetItem *nowDateTimeItem;
    QListWidgetItem *startDateTimeItem;
    QListWidgetItem *endDateTimeItem;
    QListWidgetItem *gameStatusItem;
    QListWidgetItem *playerNameItem[Shogi::PLAYER_MAX];
    QListWidgetItem *handTimeItem[Shogi::PLAYER_MAX];

};

#endif // GUI_INFORMATION_H
