#ifndef APPCONTROL_H
#define APPCONTROL_H

#include <QObject>
#include <QtGui/QDesktopWidget>
#include "mainwindow.h"
#include "appmodel.h"

class AppControl : public QObject
{
    Q_OBJECT
public:
    explicit AppControl(QObject *parent = 0);
    ~AppControl();

public slots:
    void receiveApplicationMessage(QString);

private slots:
    void recreateMainWindows();

private:
    AppModel appModelStatic;
    AppModel *appModel;
    QList<MainWindow *> mainWindowsList;
    QDesktopWidget *desktopWidget;

    void installFonts();
    void createMainWindows();
    void deleteMainWindows();
    void handleScreenChange();
};

#endif // APPCONTROL_H
