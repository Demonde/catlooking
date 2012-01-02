#include "notewidget.h"

NoteWidget::NoteWidget(QString title, QString text, QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    title(title),
    text(text)
{
    integrateWithAppModel();
}

void NoteWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent)));
}

void NoteWidget::onModelStateChanged(AppModel::ModelEvent /*modelEvent*/)
{
}
