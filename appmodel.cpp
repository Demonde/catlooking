#include <QApplication>
#include <QMutex>
#include "appmodel.h"

AppModel* AppModel::instancePointer(0);
AppModel::UiState AppModel::uiState(AppModel::OptionsState);
int AppModel::activeWidgetCounter(0);

AppModel::AppModel(QObject *parent) :
    QObject(parent)
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
