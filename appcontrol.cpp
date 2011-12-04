#include "appcontrol.h"

AppControl::AppControl(QObject *parent) :
    QObject(parent)
{
        mainWindow.show();
}

void AppControl::receiveApplicationMessage(QString message)
{
    if (message == "Hello. I'm the other instance of catlooking. I'll die. Bye.")
    {
        mainWindow.showWindow();
    }
}

