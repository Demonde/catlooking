#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QFrame>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QDir>
#include <QRegExp>
#include "appmodel.h"
#include "inactivetimer.h"

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

private slots:
    void onModelStateChanged(AppModel::ModelEvent);
    void onInactivity();

private:
    AppModel *appModel;
    InactiveTimer *mouseInactiveTimer;
    int static const inactivityTimeout;
    void setIconAndTitle();
    void integrateWithAppModel();
    void updateUi();
    void onMouseMove();
};

#endif // MAINWINDOW_H
