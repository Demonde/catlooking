#ifndef NOTELISTWIDGET_H
#define NOTELISTWIDGET_H

#include <QFrame>
#include "appmodel.h"

class NoteListWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NoteListWidget(QWidget *parent = 0);

private slots:
    void onModelStateChanged(AppModel::ModelEvent);

signals:
    void managingWidgetActivityEvent();

private:
    AppModel *appModel;
    void integrateWithAppModel();

};

#endif // NOTELISTWIDGET_H
