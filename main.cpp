#include <QtGui/QApplication>
#include <QTextCodec>
#include "appcontrol.h"
#include "singleapplication.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, "dc4cc2f94acf734f2cfb7047049d18e3"); // md5 hash of "catlooking sychev"
    if (app.isRunning())
    {
            app.sendMessage("Hello. I'm the other instance of catlooking. I'll die. Bye.");
            return 0;
    }

    AppControl *appControl = new AppControl();

    // Connection between several instances of Catlooking
    QObject::connect(&app, SIGNAL(messageAvailable(QString)), appControl, SLOT(receiveApplicationMessage(QString)));

    int returnCode;
    returnCode = app.exec();

    appControl->deleteLater();
    return returnCode;
}
