#ifndef INFORMATION_H
#define INFORMATION_H

#include <QDockWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include "shogi/shogi.h"

class Information : public QDockWidget
{
    Q_OBJECT
public:
    explicit Information(QWidget *parent = 0);
    void setShogiComponent(const Shogi::Component *component);

signals:

public slots:
    void updateNowDateTime();
    void setStartDateTime(const Shogi::DateTime &date_time);
    void setEndDateTime(const Shogi::DateTime &date_time);
    void updateSenteTimeLimit();
    void updateGoteTimeLimit();

private:
    const Shogi::Component *shogiComonent;
    QTimer *timer;
    int senteTimeLimit;
    int goteTimeLimit;
    QListWidget *widget;
    QListWidgetItem *nowDateTimeItem;
    QListWidgetItem *startDateTimeItem;
    QListWidgetItem *endDateTimeItem;
    QListWidgetItem *senteNameItem;
    QListWidgetItem *senteHandTimeItem;
    QListWidgetItem *goteNameItem;
    QListWidgetItem *goteHandTimeItem;
};

#endif // INFORMATION_H
