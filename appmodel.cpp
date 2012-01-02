#include <QApplication>
#include <QMutex>
#include "appmodel.h"
#include <QDebug>

AppModel* AppModel::instancePointer(0);

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
    emit modelWasUpdated(UiStateChanged);
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

void AppModel::importNotes()
{
    // debug
    Note* note = new Note();
    note->appendNoteState(QDateTime::currentDateTime(), "Hello", "Moto", 0);
    noteList.append(note);
    note = new Note();
    note->appendNoteState(QDateTime::currentDateTime(), "Second note", "Yes it is", 2);
    noteList.append(note);
    note = new Note();
    note->appendNoteState(QDateTime::currentDateTime(), "3 note", "Yes it is", 2);
    noteList.append(note);
    note = new Note();
    note->appendNoteState(QDateTime::currentDateTime(), "4 note", "Yes it is", 2);
    noteList.append(note);
    note = new Note();
    note->appendNoteState(QDateTime::currentDateTime(), "5 note", "Yes it is", 2);
    noteList.append(note);
    note = new Note();
    note->appendNoteState(QDateTime::currentDateTime(), "6 note", "Yes it is", 2);
    noteList.append(note);
    note = new Note();
    note->appendNoteState(QDateTime::currentDateTime(), "7 note", "Yes it is", 2);
    noteList.append(note);
    qDebug() << "Notes were imported";
    // end debug
    emit modelWasUpdated(DataChanged);
}

int AppModel::getNoteCount()
{
    return noteList.count();
}

QString AppModel::getNoteText(int noteIndex)
{
    if (noteIndex < noteList.count())
    {
        return noteList.at(noteIndex)->getText();
    }
    else
    {
        return QString();
    }
}

QString AppModel::getNoteTitle(int noteIndex)
{
    if (noteIndex < noteList.count())
    {
        return noteList.at(noteIndex)->getTitle();
    }
    else
    {
        return QString();
    }
}
