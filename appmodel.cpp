#include <QApplication>
#include <QMutex>
#include "appmodel.h"

AppModel* AppModel::instancePointer(0);
ModelInfo *AppModel::NullPointer(0);

AppModel::AppModel(QObject *parent) :
    QObject(parent),
    uiState(AppModel::OptionsState),
    activeWidgetCounter(0),
    translator(new Translator(this))
{
    QMutex creationMutex;
    creationMutex.lock();
    if (!instancePointer)
    {
        instancePointer = this;
    }
}

AppModel* AppModel::getInstance()
{
    return instancePointer;
}

void AppModel::closeApplication()
{
    uiState = AppModel::CloseState;
    emit modelWasUpdated(UiStateChanged, NullPointer);
}

AppModel::UiState AppModel::getUiState()
{
    return uiState;
}

void AppModel::reportWidgetMouseActive()
{
    ++activeWidgetCounter;
    if (activeWidgetCounter == 1)
    {
        QApplication::restoreOverrideCursor();
    }
}

void AppModel::reportWdigetMouseInactive()
{
    --activeWidgetCounter;
    if(activeWidgetCounter <= 0)
    {
        activeWidgetCounter = 0;
        QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    }
}

QString AppModel::getTranslation(QString elementId)
{
    return translator->getTranslation(elementId);
}

void AppModel::reportNoteState(QString newNoteText)
{
//    ModelEvent modelEvent = (noteEditState.text == newNoteText) ? AppModel::CursorChanged : AppModel::NoteChanged;
    noteEditState.text = newNoteText;
    emit modelWasUpdated(AppModel::NoteChanged, &noteEditState);
}

void AppModel::reportSelectionState(QTextCursor newTextCursor)
{
    noteEditState.textCursor = newTextCursor;
    emit modelWasUpdated(AppModel::CursorChanged, &noteEditState);
}
