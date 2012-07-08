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
    void onModelStateChanged(AppModel::ModelEvent modelEvent, ModelInfo * );

private:
    AppModel appModelStatic;
    AppModel *appModel;
    QList<MainWindow *> mainWindowsList;
    QDesktopWidget *desktopWidget;
    QTimer *autoSaveTimer;

    void integrateWithAppModel();
    void createMainWindows();
    void deleteMainWindows();
    void handleScreenChange();
    void setupAutoSaveTimer();

    static const int AutoSaveTimerInterval;
};

#endif // APPCONTROL_H
