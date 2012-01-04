#ifndef MANAGINGWIDGET_H
#define MANAGINGWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include "appmodel.h"

class ManagingWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ManagingWidget(QWidget *parent = 0);
    ~ManagingWidget();
    void reportOnMouseGoingInWidget();

protected:
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void mouseInsideManagingWidget();

private slots:
    void onModelStateChanged(AppModel::ModelEvent);

private:
    AppModel *appModel;
    void integrateWithAppModel();
    QPushButton *dayThemeButton;
    QPushButton *nightThemeButton;
    QPushButton *exportButton;
    QPushButton *helpButton;
    QPushButton *exitButton;
    QHBoxLayout *mainLayout;
    void setTranslations();
    void setupLayouts();
    bool reportOnMouseGoingIn;
};

#endif // MANAGINGWIDGET_H
