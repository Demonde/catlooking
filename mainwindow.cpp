#include <QShortcut>
#include <QDebug>
#include "mainwindow.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setIconAndTitle();
    createCentralWidget();
    installFonts();
    showWindow();
    connectControlSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createCentralWidget()
{
//    writerWidget = new WriterWidget(this);
//    setCentralWidget(writerWidget);
}

void MainWindow::connectControlSignals()
{
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(close()));
//    connect(writerWidget, SIGNAL(needClose()), this, SLOT(close()));
//    connect(writerWidget, SIGNAL(needMinimize()), this, SLOT(showMinimized()));
}

void MainWindow::showWindow()
{
    showNormal();
    activateWindow();
    setWindowState(windowState() | Qt::WindowFullScreen);
}

void MainWindow::receiveApplicationMessage(QString message)
{
    if (message == "Hello. I'm the other instance of catlooking. I'll die. Bye.")
    {
        showWindow();
    }
}

void MainWindow::setIconAndTitle()
{
//    QApplication::setWindowIcon(QIcon(":/images/images/catlookingwriter.png"));
    setWindowTitle(tr("Catlooking"));
}

void MainWindow::installFonts()
{
    Utils::installFont(":/fonts/fonts/LiberationSans.ttf");
    Utils::installFont(":/fonts/fonts/LiberationSerif.ttf");
}
