#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QFrame>
#include "appmodel.h"

class NoteWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NoteWidget(QString title, QString text, QWidget *parent = 0);

private slots:
    void onModelStateChanged(AppModel::ModelEvent);

signals:
    void managingWidgetActivityEvent();

private:
    AppModel *appModel;
    QString title;
    QString text;
    void integrateWithAppModel();

};

#endif // NOTEWIDGET_H
