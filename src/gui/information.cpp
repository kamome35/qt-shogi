#include "information.h"

#include <QTimer>
#include "shogi/component.h"

Information::Information(QWidget *parent) :
    QDockWidget(parent)
{
    setWindowTitle(tr("対局情報"));

    widget = new QListWidget(this);

    nowDateTimeItem = new QListWidgetItem(widget);
    startDateTimeItem = new QListWidgetItem(widget);
    endDateTimeItem = new QListWidgetItem(widget);
    senteNameItem = new QListWidgetItem(widget);
    senteHandTimeItem = new QListWidgetItem(widget);
    goteNameItem = new QListWidgetItem(widget);
    goteHandTimeItem = new QListWidgetItem(widget);

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();


    setWidget(widget);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateNowDateTime()));
}

void Information::setShogiComponent(const Shogi::Component *component)
{
    shogiComonent = component;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSenteTimeLimit()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGoteTimeLimit()));
}

void Information::updateNowDateTime()
{
    nowDateTimeItem->setText(tr("現在時刻: ") + QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
}

void Information::setStartDateTime(const Shogi::DateTime &date_time)
{
    startDateTimeItem->setText(tr("開始時間: ") + date_time.toString("yyyy/MM/dd hh:mm:ss"));
}

void Information::setEndDateTime(const Shogi::DateTime &date_time)
{
    endDateTimeItem->setText(tr("終了時間: ") + date_time.toString("yyyy/MM/dd hh:mm:ss"));
}

void Information::updateSenteTimeLimit()
{
    senteTimeLimit -= 1;
    senteHandTimeItem->setText(tr(" 残り時間: %1:%2").arg(senteTimeLimit/60).arg(senteTimeLimit%60));
}

void Information::updateGoteTimeLimit()
{
    goteTimeLimit -= 1;
    goteHandTimeItem->setText(tr(" 残り時間: %1:%2").arg(goteTimeLimit/60).arg(goteTimeLimit%60));
}
