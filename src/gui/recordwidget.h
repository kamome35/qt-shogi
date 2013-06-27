#ifndef BATTLERECORD_H
#define BATTLERECORD_H

#include <QDockWidget>
#include <QListWidget>

#include "shogi/shogi.h"

class RecordWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit RecordWidget(QWidget *parent = 0);

signals:

public slots:
    void init();
    void recordUpdate(const Shogi::Record &record);

private:
    QListWidget *widget;
};

#endif // BATTLERECORD_H
