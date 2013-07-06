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

Shogi::String GameStartDialog::sentePlayerName() const
{
    return !ui->sentePlayerName->text().isEmpty() ? ui->sentePlayerName->text() : tr("No Name");
}

Shogi::String GameStartDialog::gotePlayerName() const
{
    return !ui->gotePlayerName->text().isEmpty() ? ui->gotePlayerName->text() : tr("No Name");
}

Shogi::Time GameStartDialog::timeLimit() const
{
    return ui->limitTime->time();
}
