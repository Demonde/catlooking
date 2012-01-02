#include "notelistwidget.h"

NoteListWidget::NoteListWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance())
{
    integrateWithAppModel();
}

void NoteListWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent)));
}

void NoteListWidget::onModelStateChanged(AppModel::ModelEvent modelEvent)
{
    if (AppModel::DataChanged == modelEvent)
    {
        deleteAllNoteWidgets();
        createNoteWidgets();
    }
}

void NoteListWidget::deleteAllNoteWidgets()
{
    while(!noteWidgetList.isEmpty())
    {
        noteWidgetList.first()->deleteLater();
        noteWidgetList.removeFirst();
    }
}

void NoteListWidget::createNoteWidgets()
{
    int noteTotalCount = appModel->getNoteCount();
    for (int i = 0; i < noteTotalCount; ++i)
    {
        NoteWidget* noteWidget = new NoteWidget(appModel->getNoteTitle(i),
                                                appModel->getNoteTitle(i),
                                                this);
        noteWidgetList.append(noteWidget);
    }
}
