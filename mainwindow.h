#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QFrame>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QDir>
#include <QRegExp>

class MainWindow : public QFrame
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showWindow();

private:
    void setIconAndTitle();
    void installFonts();
    void createCentralWidget();
    void connectControlSignals();
};

#endif // MAINWINDOW_H
