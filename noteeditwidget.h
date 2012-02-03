#ifndef NOTEEDITWIDGET_H
#define NOTEEDITWIDGET_H

#include <QFrame>
#include <QTextEdit>
#include <QTimer>
#include "appmodel.h"

class NoteEditWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NoteEditWidget(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void onModelStateChanged(AppModel::ModelEvent modelEvent, ModelInfo *infoPointer);
    void reportNoteState();
    void reportSelectionState();

private:
    AppModel *appModel;
    void integrateWithAppModel();
    QTextEdit *textEdit;
    QFrame* visualCover;
//    QTimer* noteStateReporter;
    void setupVisualCover();
    static const int textEditVerticalMargin;
};

#endif // NOTEEDITWIDGET_H
