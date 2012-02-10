#include <QShortcut>
#include <QFile>
#include <QDebug>
#include "mainwindow.h"

int const MainWindow::inactivityTimeout(3000);
int const MainWindow::managingWidgetWidth(600);
int const MainWindow::managingWidgetHeight(50);
int const MainWindow::mouseMoveCheckingTimer(500);

MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent),
      appModel(AppModel::getInstance()),
      mouseInactiveTimer(new InactiveTimer(inactivityTimeout, this)),
      managingWidget(new ManagingWidget(this)),
      managingWidgetAnimation(new QPropertyAnimation(managingWidget, "geometry")),
      managingWidgetShownGeometry(QRect(0, 0, 0, 0)),
      managingWidgetHiddenGeometry(QRect(0, 0, 0, 0)),
      noteEditWidget(new NoteEditWidget(this)),
      mouseMoveTimer(new QTimer(this)),
      oldMousePosition(QCursor::pos())
{
    setIconAndTitle();
    showWindow();
    integrateWithAppModel();
    setupInactivityMonitor();
    setupStyleSheet();
    managingWidget->raise();
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent (QCloseEvent  *)
{
    appModel->closeApplication();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    setManagingWidgetInitialGeometry();
    noteEditWidget->setGeometry(0, 0, width(), height());
}

void MainWindow::onModelStateChanged(AppModel::ModelEvent modelEvent, ModelInfo * /*dataPointer*/)
{
    if (AppModel::UiStateChanged == modelEvent)
    {
        updateUi();
    }
}

void MainWindow::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, ModelInfo *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, ModelInfo *)));
}

void MainWindow::showWindow()
{
    show();
    activateWindow();
    setWindowState(windowState() | Qt::WindowFullScreen);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

void MainWindow::setupStyleSheet(AppModel::UiTheme theme)
{
    QFile qssGeneralFile(":/qss/resources/qss/mainwindow.qss");
    qssGeneralFile.open(QFile::ReadOnly);
    QFile qssThemeFile;
    if(AppModel::DayTheme == theme)
    {
        qssThemeFile.setFileName(":/qss/resources/qss/daytheme.qss");
    }
    else
    {
        qssThemeFile.setFileName(":/qss/resources/qss/darktheme.qss");
    }
    qssThemeFile.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(qssGeneralFile.readAll()) + QLatin1String(qssThemeFile.readAll()));
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
    connect(mouseInactiveTimer, SIGNAL(inactivityDetected()), this, SLOT(onInactivity()));
    connect(managingWidget, SIGNAL(mouseInsideManagingWidget()),
            mouseInactiveTimer, SLOT(pauseTicker()));

    mouseMoveTimer->setInterval(mouseMoveCheckingTimer);
    mouseMoveTimer->start();
    connect(mouseMoveTimer, SIGNAL(timeout()), this, SLOT(checkMouseMovement()));
}

void MainWindow::onInactivity()
{
    appModel->reportWdigetMouseInactive();
    hideManagingWidget();
}

void MainWindow::onMouseMove()
{
    managingWidget->reportOnMouseGoingInWidget();
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
    managingWidgetAnimation->setEndValue(managingWidgetHiddenGeometry);
    managingWidgetAnimation->start();
    noteEditWidget->setFocus();
}

void MainWindow::checkMouseMovement()
{
    if(QCursor::pos() != oldMousePosition)
    {
        oldMousePosition = QCursor::pos();
        if(geometry().contains(QCursor::pos()))
        {
            onMouseMove();
        }
    }
}
