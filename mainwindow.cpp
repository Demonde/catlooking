#include <QShortcut>
#include <QDebug>
#include "mainwindow.h"

int const MainWindow::inactivityTimeout(1000);

MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent),
      appModel(AppModel::getInstance()),
      mouseInactiveTimer(new InactiveTimer(inactivityTimeout, this))
{
    setIconAndTitle();
    showWindow();
    integrateWithAppModel();

    setMouseTracking(true);
    connect(mouseInactiveTimer, SIGNAL(inactivityDetected()), this, SLOT(onInactivity()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::mouseMoveEvent(QMouseEvent  *)
{
    mouseInactiveTimer->notifyActivity();
    onMouseMove();
}

void MainWindow::onModelStateChanged(AppModel::ModelEvent modelEvent)
{
    if (AppModel::UiStateChanged == modelEvent)
    {
        updateUi();
    }
}

void MainWindow::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent)));

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcut, SIGNAL(activated()), appModel, SLOT(closeApplication()));
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

void MainWindow::updateUi()
{
    if(AppModel::CloseState == appModel->getUiState())
    {
        close();
    }
}

void MainWindow::onInactivity()
{
    qDebug() << "Inactivity!";
}

void MainWindow::onMouseMove()
{
    qDebug() << "Mouse moved!";
}
