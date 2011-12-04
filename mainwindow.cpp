#include <QShortcut>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent),
      appModel(AppModel::getInstance())
{
    setIconAndTitle();
    createCentralWidget();
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

void MainWindow::setIconAndTitle()
{
//    QApplication::setWindowIcon(QIcon(":/images/images/catlookingwriter.png"));
    setWindowTitle(tr("Catlooking"));
}
