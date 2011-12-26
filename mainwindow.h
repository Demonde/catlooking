#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QFrame>
#include <QSettings>
#include <QPropertyAnimation>
#include "appmodel.h"
#include "inactivetimer.h"
#include "managingwidget.h"
#include "notelistwidget.h"

class MainWindow : public QFrame
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showWindow();

protected:
    void mouseMoveEvent(QMouseEvent  *);
    void closeEvent (QCloseEvent  *);
    void resizeEvent(QResizeEvent *);

private slots:
    void onModelStateChanged(AppModel::ModelEvent);
    void onInactivity();

private:
    AppModel *appModel;
    InactiveTimer *mouseInactiveTimer;
    ManagingWidget *managingWidget;
    QPropertyAnimation *managingWidgetAnimation;
    QRect managingWidgetShownGeometry;
    QRect managingWidgetHiddenGeometry;
    NoteListWidget *noteListWidget;
    QPropertyAnimation *noteListWidgetAnimation;
    QRect noteListWidgetShownGeometry;
    QRect noteListWidgetHiddenGeometry;
    int static const inactivityTimeout;
    int static const managingWidgetWidth;
    int static const managingWidgetHeight;
    int static const noteListWidgetVerticalMargin;
    int static const noteListWidgetWidth;
    void setupStyleSheet();
    void setIconAndTitle();
    void integrateWithAppModel();
    void updateUi();
    void setupInactivityMonitor();
    void onMouseMove();
    void setManagingWidgetInitialGeometry();
    void showManagingWidget();
    void hideManagingWidget();
    void setNoteListWidgetInitialGeometry();
    void showNoteListWidget();
    void hideNoteListWidget();
};

#endif // MAINWINDOW_H
