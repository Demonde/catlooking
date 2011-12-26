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

void NoteListWidget::onModelStateChanged(AppModel::ModelEvent /*modelEvent*/)
{
}
