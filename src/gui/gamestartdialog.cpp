#include "gamestartdialog.h"
#include "ui_gamestartdialog.h"
#include <QLineEdit>

GameStartDialog::GameStartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameStartDialog)
{
    ui->setupUi(this);
}

GameStartDialog::~GameStartDialog()
{
    delete ui;
}

Shogi::String GameStartDialog::playerName(Shogi::Player player) const
{
    if (player == Shogi::Sente)
        return !ui->sentePlayerName->text().isEmpty() ? ui->sentePlayerName->text() : tr("No Name");
    else
        return !ui->gotePlayerName->text().isEmpty() ? ui->gotePlayerName->text() : tr("No Name");
}

Shogi::HumanType GameStartDialog::humanType(Shogi::Player player) const
{
    if (player == Shogi::Sente)
        return static_cast<Shogi::HumanType>(ui->senteHumanType->currentIndex());
    else
        return static_cast<Shogi::HumanType>(ui->goteHumanType->currentIndex());
}

Shogi::Time GameStartDialog::timeLimit() const
{
    return ui->limitTime->time();
}
