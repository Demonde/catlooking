#ifndef NOTEEDITWIDGET_H
#define NOTEEDITWIDGET_H

#include <QFrame>
#include <QTextEdit>
#include "appmodel.h"

class NoteEditWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NoteEditWidget(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void onModelStateChanged(AppModel::ModelEvent, const void *);

private:
    AppModel *appModel;
    void integrateWithAppModel();
    QTextEdit *textEdit;
    QFrame* visualCover;
    void setupVisualCover();
};

#endif // NOTEEDITWIDGET_H
