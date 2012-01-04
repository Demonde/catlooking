#ifndef NOTEEDIT_H
#define NOTEEDIT_H

#include <QPlainTextEdit>
#include "appmodel.h"

class NoteEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit NoteEdit(QWidget *parent = 0);

private slots:
    void onModelStateChanged(AppModel::ModelEvent, const void *);

private:
    AppModel *appModel;
    void integrateWithAppModel();
};

#endif // NOTEEDIT_H
