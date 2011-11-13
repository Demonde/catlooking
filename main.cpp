#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "singleapplication.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, "dc4cc2f94acf734f2cfb7047049d18e3"); // md5 hash of "catlooking sychev"
    if (app.isRunning())
    {
            app.sendMessage("Hello. I'm the other instance of catlooking. I'll die. Bye.");
            return 0;
    }

    MainWindow *mainWindow = new MainWindow();

    // Connection between several instances of Catlooking
    QObject::connect(&app, SIGNAL(messageAvailable(QString)), mainWindow, SLOT(receiveApplicationMessage(QString)));
    mainWindow->show();

    int returnCode;
    returnCode = app.exec();

    delete mainWindow;
    return returnCode;
}
