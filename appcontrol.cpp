#include <QtGui/QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <QFile> //debug
#include "appcontrol.h"

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
    QFontDatabase::addApplicationFont("./fonts/chinese.ttc");
    QFontDatabase::addApplicationFont("./fonts/designosaur-italic.ttf");
//    int result1 = QFontDatabase::addApplicationFont("./fonts/chinese.ttc");
//    int result2 = QFontDatabase::addApplicationFont("./fonts/designosaur-italic.ttf");
//    qDebug() << "Result1 =" << result1 << "Result2 =" << result2;
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
