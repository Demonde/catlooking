#include <QShortcut>
#include <QFile>
#include <QDebug>
#include "mainwindow.h"

int const MainWindow::inactivityTimeout(5000);
int const MainWindow::managingWidgetWidth(600);
int const MainWindow::managingWidgetHeight(90);

MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent),
      appModel(AppModel::getInstance()),
      mouseInactiveTimer(new InactiveTimer(inactivityTimeout, this)),
      managingWidget(new ManagingWidget(this)),
      managingWidgetAnimation(new QPropertyAnimation(managingWidget, "geometry")),
      managingWidgetShownGeometry(QRect(0, 0, 0, 0)),
      managingWidgetHiddenGeometry(QRect(0, 0, 0, 0))
{
    setIconAndTitle();
    showWindow();
    integrateWithAppModel();
    setupInactivityMonitor();
    setupStyleSheet();
}

MainWindow::~MainWindow()
{
}

void MainWindow::mouseMoveEvent(QMouseEvent  *)
{
    onMouseMove();
}

void MainWindow::closeEvent(QCloseEvent  *)
{
    appModel->closeApplication();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    setManagingWidgetInitialGeometry();
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
}

void MainWindow::showWindow()
{
    show();
    activateWindow();
    setWindowState(windowState() | Qt::WindowFullScreen);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

void MainWindow::setupStyleSheet()
{
    QFile qssFile(":/qss/resources/qss/mainwindow.qss");
    qssFile.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(qssFile.readAll()));
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

void MainWindow::setupInactivityMonitor()
{
    setMouseTracking(true);
    connect(mouseInactiveTimer, SIGNAL(inactivityDetected()), this, SLOT(onInactivity()));
    connect(managingWidget, SIGNAL(managingWidgetActivityEvent()),
            mouseInactiveTimer, SLOT(notifyActivity()));
}

void MainWindow::onInactivity()
{
    appModel->reportWdigetMouseInactive();
    hideManagingWidget();
}

void MainWindow::onMouseMove()
{
    if(!mouseInactiveTimer->isActionPresence())
    {
        appModel->reportWidgetMouseActive();
        showManagingWidget();
    }
    mouseInactiveTimer->notifyActivity();
}

void MainWindow::setManagingWidgetInitialGeometry()
{
    int xPoint = (width() - managingWidgetWidth) / 2;
    managingWidgetHiddenGeometry = QRect(xPoint, - managingWidgetHeight,
                                      managingWidgetWidth, managingWidgetHeight);
     managingWidgetShownGeometry = QRect(xPoint, 0,
                                         managingWidgetWidth, managingWidgetHeight);
    managingWidget->setGeometry(managingWidgetHiddenGeometry);
}

void MainWindow::showManagingWidget()
{
    managingWidgetAnimation->setEndValue(managingWidgetShownGeometry);
    managingWidgetAnimation->start();
}

void MainWindow::hideManagingWidget()
{
    managingWidget->clearFocusFromTitleEdit();
    managingWidgetAnimation->setEndValue(managingWidgetHiddenGeometry);
    managingWidgetAnimation->start();
}
