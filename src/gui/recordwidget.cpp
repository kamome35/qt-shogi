#include "recordwidget.h"

RecordWidget::RecordWidget(QWidget *parent) :
    QDockWidget(parent)
{
    setWindowTitle(tr("棋譜"));

    widget = new QListWidget(this);
    setWidget(widget);
}

void RecordWidget::init()
{
    widget->clear();
}

void RecordWidget::recordUpdate(const Shogi::Record &record)
{
    Q_UNUSED(record);
}
