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
    void onModelStateChanged(AppModel::ModelEvent modelEvent, const ModelInfo *infoPointer);
    void onTextChanged();

private:
    AppModel *appModel;
    void integrateWithAppModel();
    QTextEdit *textEdit;
    QFrame* visualCover;
    void setupVisualCover();
    static const int textEditVerticalMargin;
};

#endif // NOTEEDITWIDGET_H
