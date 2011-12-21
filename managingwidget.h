#ifndef MANAGINGWIDGET_H
#define MANAGINGWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "appmodel.h"

class ManagingWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ManagingWidget(QWidget *parent = 0);
    ~ManagingWidget();
    void clearFocusFromTitleEdit();

private slots:
    void onModelStateChanged(AppModel::ModelEvent);

signals:
    void managingWidgetActivityEvent();

private:
    AppModel *appModel;
    void integrateWithAppModel();
    QPushButton *dayThemeButton;
    QPushButton *nightThemeButton;
    QPushButton *exportButton;
    QPushButton *helpButton;
    QPushButton *exitButton;
    QLabel *titleLabel;
    QLineEdit *titleLineEdit;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topButtonsLayout;
    QHBoxLayout *titleLayout;
    void setTranslations();
    void setupLayouts();
};

#endif // MANAGINGWIDGET_H
