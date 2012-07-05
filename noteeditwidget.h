#ifndef NOTEEDITWIDGET_H
#define NOTEEDITWIDGET_H

#include <QFrame>
#include <QTextEdit>
#include <QTimer>
#include <QPropertyAnimation>
#include "appmodel.h"

class NoteEditWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NoteEditWidget(QWidget *parent = 0);
    void adjustTextEditPosition();
    void resetTextEditPosition();

public slots:
    void setFocus();

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
    void setupVisualCover();
    int noteEditHeight;
    int noteEditWidth;
    int noteEditXPos;
    int noteEditYPos;
    QPropertyAnimation *textEditAnimation;
    static const int TextEditVerticalMargin;
    static const QString CiceroTextSample;
    static const QFont getFontForTextEditWith(const int width);
    static const int LineHeightPercentage;
    static const float NoteEditWidthMultiplier;
    static const int TextEditAnimationDuration;
    static const int TextEditTextCursorCaretDeadZone;
};

#endif // NOTEEDITWIDGET_H
