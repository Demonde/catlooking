#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QFrame>
#include <QSettings>
#include <QPropertyAnimation>
#include "appmodel.h"
#include "inactivetimer.h"
#include "managingwidget.h"
#include "noteeditwidget.h"

class MainWindow : public QFrame
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupStyleSheet(AppModel::UiTheme theme = AppModel::DayTheme);

public slots:
    void showWindow();

protected:
    void closeEvent (QCloseEvent  *);
    void resizeEvent(QResizeEvent *);
    void wheelEvent(QWheelEvent *);

private slots:
    void onModelStateChanged(AppModel::ModelEvent, ModelInfo *);
    void onInactivity();
    void checkMouseMovement();

private:
    AppModel *appModel;
    InactiveTimer *mouseInactiveTimer;
    ManagingWidget *managingWidget;
    QPropertyAnimation *managingWidgetAnimation;
    QRect managingWidgetShownGeometry;
    QRect managingWidgetHiddenGeometry;
    int static const inactivityTimeout;
    int static const managingWidgetWidth;
    int static const managingWidgetHeight;
    void setIconAndTitle();
    void integrateWithAppModel();
    void updateUi();
    void setupInactivityMonitor();
    void onMouseMove();
    void setManagingWidgetInitialGeometry();
    void showManagingWidget();
    void hideManagingWidget();
    NoteEditWidget *noteEditWidget;
    QTimer *mouseMoveTimer;
    QPoint oldMousePosition;
    int static const mouseMoveCheckingTimer;
};

#endif // MAINWINDOW_H
