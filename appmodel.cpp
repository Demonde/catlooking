#include <QMutex>
#include "appmodel.h"

AppModel* AppModel::instancePointer(0);
AppModel::UiState AppModel::uiState(AppModel::OptionsState);

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
