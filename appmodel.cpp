#include <QMutex>
#include "appmodel.h"

AppModel* AppModel::instancePointer(0);

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
