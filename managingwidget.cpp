#include "managingwidget.h"

ManagingWidget::ManagingWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance())
{
}

void ManagingWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent)));
}

void ManagingWidget::onModelStateChanged(AppModel::ModelEvent modelEvent)
{
    if (AppModel::UiStateChanged == modelEvent)
    {
    }
}
