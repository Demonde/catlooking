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

private slots:
    void onModelStateChanged(AppModel::ModelEvent, ModelInfo *);
    void askForExport();

private:
    AppModel *appModel;
    void integrateWithAppModel();
    QPushButton *dayThemeButton;
    QPushButton *darkThemeButton;
    QPushButton *exportButton;
    QPushButton *eraseButton;
    QPushButton *exitButton;
    QHBoxLayout *mainLayout;
    void setTranslations();
    void setupLayouts();
    bool reportOnMouseGoingIn;
};

#endif // MANAGINGWIDGET_H
