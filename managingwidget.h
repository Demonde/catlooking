#ifndef MANAGINGWIDGET_H
#define MANAGINGWIDGET_H

#include <QFrame>
#include "appmodel.h"

class ManagingWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ManagingWidget(QWidget *parent = 0);

private slots:
    void onModelStateChanged(AppModel::ModelEvent);

private:
    AppModel *appModel;
    void integrateWithAppModel();

};

#endif // MANAGINGWIDGET_H
