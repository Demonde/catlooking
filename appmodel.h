#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>

class AppModel : public QObject
{
    Q_OBJECT
public:
    explicit AppModel(QObject *parent = 0);
    static AppModel* getInstance();

signals:

private:
    static AppModel* instancePointer;
};

#endif // APPMODEL_H
