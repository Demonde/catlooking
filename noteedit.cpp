#include "noteedit.h"

NoteEdit::NoteEdit(QWidget *parent) :
    QPlainTextEdit(parent),
    appModel(AppModel::getInstance())
{
    integrateWithAppModel();
}

void NoteEdit::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, const void *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, const void *)));
}

void NoteEdit::onModelStateChanged(AppModel::ModelEvent, const void * /*dataPointer*/)
{
}
