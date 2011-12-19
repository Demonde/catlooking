#include <QtGui/QApplication>
#include <QDebug>
#include "appcontrol.h"
#include "utils.h"

AppControl::AppControl(QObject *parent) :
    QObject(parent),
    appModel(AppModel::getInstance()),
    desktopWidget(QApplication::desktop())
{
    installFonts();
    createMainWindows();
    handleScreenChange();
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
    Utils::installFont(":/fonts/resources/fonts/chinese.ttc");
//    Utils::installFont(":/fonts/fonts/LiberationSerif.ttc");
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
