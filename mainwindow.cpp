#include <QShortcut>
#include <QFile>
#include <QApplication>
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

void MainWindow::wheelEvent(QWheelEvent *)
{
    onMouseMove();
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
#ifdef Q_WS_WIN
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
#endif
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
    QApplication::setWindowIcon(QIcon(":/qss/resources/qss/catlooking.png"));
    setWindowTitle(AppModel::ApplicationName);
}

void MainWindow::updateUi()
{
    if(AppModel::CloseState == appModel->getUiState())
    {
        close();
    }
    if(AppModel::EditState == appModel->getUiState())
    {
        if(this->isEnabled())
        {
            noteEditWidget->setFocus();
        }
    }
}

void MainWindow::setupInactivityMonitor()
{
    connect(mouseInactiveTimer, SIGNAL(inactivityDetected()), this, SLOT(onInactivity()));
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
    if(!mouseInactiveTimer->isActionPresence())
    {
        appModel->reportWidgetMouseActive();
        showManagingWidget();
        noteEditWidget->resetTextEditPosition();
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
    noteEditWidget->adjustTextEditPosition();
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
