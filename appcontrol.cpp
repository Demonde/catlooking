#include "appcontrol.h"
#include "utils.h"

AppControl::AppControl(QObject *parent) :
    QObject(parent)
{
        mainWindow.show();
        installFonts();
}

void AppControl::receiveApplicationMessage(QString message)
{
    if (message == "Hello. I'm the other instance of catlooking. I'll die. Bye.")
    {
        mainWindow.showWindow();
    }
}

void AppControl::installFonts()
{
//    Utils::installFont(":/fonts/fonts/LiberationSans.ttf");
//    Utils::installFont(":/fonts/fonts/LiberationSerif.ttf");
}
