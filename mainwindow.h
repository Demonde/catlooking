#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QDir>
#include <QRegExp>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void receiveApplicationMessage(QString);

private slots:
    void showWindow();

private:
//    WriterWidget *writerWidget;
    void setIconAndTitle();
    void installFonts();
    void createCentralWidget();
    void connectControlSignals();
};

#endif // MAINWINDOW_H
