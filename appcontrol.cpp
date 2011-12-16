#include <QtGui/QDesktopWidget>
#include <QtGui/QApplication>
#include <QDebug>
#include "appcontrol.h"
#include "utils.h"

AppControl::AppControl(QObject *parent) :
    QObject(parent),
    appModel(AppModel::getInstance())
{
    installFonts();
    createMainWindows();
}

AppControl::~AppControl()
{
    deleteMainWindows();
}

void AppControl::receiveApplicationMessage(QString message)
{
    if (message == "Hello. I'm the other instance of catlooking. I'll die. Bye.")
    {
        recreateMainWindows();
    }
}

void AppControl::installFonts()
{
    //    Utils::installFont(":/fonts/fonts/LiberationSans.ttf");
    //    Utils::installFont(":/fonts/fonts/LiberationSerif.ttf");
}

void AppControl::createMainWindows()
{
    QDesktopWidget *desktopWidget = QApplication::desktop();
    int screenCount = desktopWidget->screenCount();
    for (int i = 0; i < screenCount; ++i)
    {
        MainWindow *mainWindow = new MainWindow();
        mainWindowsList.append(mainWindow);
        mainWindow->setGeometry(desktopWidget->screenGeometry(i));
        mainWindow->setWindowState(mainWindow->windowState() | Qt::WindowFullScreen);
        mainWindow->setWindowFlags(mainWindow->windowFlags() | Qt::WindowStaysOnTopHint);
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
