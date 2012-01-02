#ifndef NOTELISTWIDGET_H
#define NOTELISTWIDGET_H

#include <QFrame>
#include <QList>
#include <QScrollBar>
#include "appmodel.h"
#include "notewidget.h"

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
    QScrollBar *scrollBar;
    void integrateWithAppModel();
    QList< NoteWidget* > noteWidgetList;
    void deleteAllNoteWidgets();
    void createNoteWidgets();
};

#endif // NOTELISTWIDGET_H
