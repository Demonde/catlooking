#include <QtGui/QApplication>
#include <QFontDatabase>
#include <QDebug>
#include "appcontrol.h"

AppControl::AppControl(QObject *parent) :
    QObject(parent),
    appModel(AppModel::getInstance()),
    desktopWidget(QApplication::desktop())
{
    integrateWithAppModel();
    createMainWindows();
    handleScreenChange();
    appModel->restoreText();
}

AppControl::~AppControl()
{
    deleteMainWindows();
}

void AppControl::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, ModelInfo *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, ModelInfo *)));
}

void AppControl::receiveApplicationMessage(QString message)
{
    if (message == "Hello. I'm the other instance of catlooking. I'll die. Bye.")
    {
        recreateMainWindows();
    }
}

void AppControl::onModelStateChanged(AppModel::ModelEvent modelEvent, ModelInfo */*infoPointer*/)
{
    if (AppModel::DayThemeEnabled == modelEvent)
    {
        foreach(MainWindow* window, mainWindowsList)
        {
            window->setupStyleSheet(AppModel::DayTheme);
        }
    }
    if (AppModel::DarkThemeEnabled == modelEvent)
    {
        foreach(MainWindow* window, mainWindowsList)
        {
            window->setupStyleSheet(AppModel::DarkTheme);
        }
    }
}

void AppControl::createMainWindows()
{
    int screenCount = desktopWidget->screenCount();
    for (int i = 0; i < screenCount; ++i)
    {
        MainWindow *mainWindow = new MainWindow();
        mainWindowsList.append(mainWindow);
        mainWindow->setGeometry(desktopWidget->screenGeometry(i));
        mainWindow->showWindow();
    }
}

void AppControl::deleteMainWindows()
{
    while (!mainWindowsList.isEmpty())
    {
        mainWindowsList.takeFirst()->deleteLater();
    }
}

void AppControl::recreateMainWindows()
{
    deleteMainWindows();
    createMainWindows();
}

void AppControl::handleScreenChange()
{
    connect(desktopWidget, SIGNAL(workAreaResized(int)),
            this, SLOT(recreateMainWindows()));
}
