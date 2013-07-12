#include "information.h"

#include <QTimer>

using namespace Shogi;

Information::Information(QWidget *parent) :
    QDockWidget(parent)
{
    setWindowTitle(tr("対局情報"));

    widget = new QListWidget(this);

    nowDateTimeItem = new QListWidgetItem(widget);
    startDateTimeItem = new QListWidgetItem(widget);
    endDateTimeItem = new QListWidgetItem(widget);
    gameStatusItem = new QListWidgetItem(widget);
    playerNameItem[Sente] = new QListWidgetItem(widget);
    handTimeItem[Sente] = new QListWidgetItem(widget);
    playerNameItem[Gote] = new QListWidgetItem(widget);
    handTimeItem[Gote] = new QListWidgetItem(widget);

    timer = new QTimer(this);
    timer->setInterval(500);
    timer->start();

    setWidget(widget);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateNowDateTime()));
}

void Information::setShogiComponent(const ShogiComponent *component)
{
    sec_counter.start();
    shogiComonent = component;
    playerNameItem[Sente]->setText(tr("☗") + component->playerName(Sente));
    playerNameItem[Gote]->setText(tr("☖") + component->playerName(Gote));
    handTimeItem[Sente]->setText(tr(" 残り時間: %1").arg(shogiComonent->timeLimit(Sente).toString("hh:mm:ss")));
    handTimeItem[Gote]->setText(tr(" 残り時間: %1").arg(shogiComonent->timeLimit(Gote).toString("hh:mm:ss")));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeLimit()));
    connect(component, SIGNAL(gameStart()), this, SLOT(setStartDateTime()));
    connect(component, SIGNAL(gameEnd()), this, SLOT(setEndDateTime()));
    connect(component, SIGNAL(gameStart()), this, SLOT(setGameStatusItem()));
    connect(component, SIGNAL(gameEnd()), this, SLOT(setGameStatusItem()));
    connect(component, SIGNAL(changeGameStatus(Shogi::GameStatus)), this, SLOT(setGameStatusItem(Shogi::GameStatus)));
    connect(component, SIGNAL(changeTurn(Shogi::Player)), this, SLOT(changedTurn()));
}

void Information::updateNowDateTime()
{
    nowDateTimeItem->setText(tr("現在時刻: ") + QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
}

void Information::setStartDateTime()
{
    startDateTimeItem->setText(tr("開始時間: ") + shogiComonent->startDateTime().toString("yyyy/MM/dd hh:mm:ss"));
}

void Information::setEndDateTime()
{
    endDateTimeItem->setText(tr("終了時間: ") + shogiComonent->endDateTime().toString("yyyy/MM/dd hh:mm:ss"));
}

void Information::setGameStatusItem()
{
    setGameStatusItem(shogiComonent->gameStatus());
}

void Information::setGameStatusItem(Shogi::GameStatus game_status)
{
#define GameStatusToText(game_status) game_status == StatusStandBy ? "対局開始待ち" : \
                                      game_status == StatusPlaying ? "対局中" : \
                                      game_status == StatusToryo ? "投了" : \
                                      game_status == StatusChudan ? "中断" : \
                                      game_status == StatusSennichite ? "千日手" : \
                                      game_status == StatusTimeUp ? "手番側が時間切れで負け" : \
                                      game_status == StatusIllegalMove ? "手番側の反則負け" : \
                                      game_status == StatusJishogi ? "持将棋" : \
                                      game_status == StatusKachi ? "勝ちの宣言" : \
                                      game_status == StatusHikiwake ? "引き分けの宣言" : \
                                      game_status == StatusTsumi ? "詰み" : \
                                      game_status == StatusFuzumi ? "不詰" : \
                                      game_status == StatusError ? "エラー" : \
                                      "不明"

    gameStatusItem->setText(tr("状態: ") + tr(GameStatusToText(game_status)));
}

void Information::updateTimeLimit()
{
    Player turn = shogiComonent->turn();
    handTimeItem[turn]->setText(tr(" 残り時間: %1").arg(shogiComonent->timeLimit(turn).addMSecs(-sec_counter.elapsed()).toString("hh:mm:ss")));
    handTimeItem[turn]->setBackground(QColor("#ffff00"));
    handTimeItem[enemy(turn)]->setBackground(QColor("#ffffff"));
}

void Information::changedTurn()
{
    sec_counter.restart();
}
