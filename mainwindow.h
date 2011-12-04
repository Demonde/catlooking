#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QFrame>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QDir>
#include <QRegExp>
#include "appmodel.h"

class MainWindow : public QFrame
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showWindow();

private slots:
    void onModelStateChanged(AppModel::ModelEvent);

private:
    AppModel *appModel;
    void setIconAndTitle();
    void integrateWithAppModel();
    void updateUi();
};

#endif // MAINWINDOW_H
