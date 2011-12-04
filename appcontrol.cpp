#include <QtGui/QDesktopWidget>
#include <QtGui/QApplication>
#include "appcontrol.h"
#include "utils.h"

AppControl::AppControl(QObject *parent) :
    QObject(parent),
    appModel(AppModel::getInstance())
{
    installFonts();
    createMainWindows();
    showMainWindows();
}

AppControl::~AppControl()
{
    deleteMainWindows();
}

void AppControl::receiveApplicationMessage(QString message)
{
    if (message == "Hello. I'm the other instance of catlooking. I'll die. Bye.")
    {
        showMainWindows();
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
    }
}

void AppControl::deleteMainWindows()
{
    while (!mainWindowsList.isEmpty())
    {
        mainWindowsList.takeFirst()->deleteLater();
    }
}

void AppControl::showMainWindows()
{
    MainWindow *mainWindow;
    foreach(mainWindow, mainWindowsList)
    {
        mainWindow->showWindow();
    }
}
