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
    ~AppControl();

public slots:
    void receiveApplicationMessage(QString);

private:
    AppModel appModelStatic;
    AppModel *appModel;
    QList<MainWindow *> mainWindowsList;

    void installFonts();
    void createMainWindows();
    void deleteMainWindows();
    void showMainWindows();
};

#endif // APPCONTROL_H
