#ifndef APPCONTROL_H
#define APPCONTROL_H

#include <QObject>
#include "mainwindow.h"
#include "appmodel.h"

class AppControl : public QObject
{
    Q_OBJECT
public:
    explicit AppControl(QObject *parent = 0);

public slots:
    void receiveApplicationMessage(QString);

private:
    AppModel appModel;
    MainWindow mainWindow;

    void installFonts();
};

#endif // APPCONTROL_H
