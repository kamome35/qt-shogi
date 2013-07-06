#ifndef GUI_GAMESTARTDIALOG_H
#define GUI_GAMESTARTDIALOG_H

#include <QDialog>

#include <shogi/shogi.h>

namespace Ui {
class GameStartDialog;
}

class GameStartDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameStartDialog(QWidget *parent = 0);
    ~GameStartDialog();
    Shogi::String sentePlayerName() const;
    Shogi::String gotePlayerName() const;
    int timeLimit() const;
    
private:
    Ui::GameStartDialog *ui;
};

#endif // GUI_GAMESTARTDIALOG_H
