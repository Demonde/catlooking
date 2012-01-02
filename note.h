#ifndef NOTE_H
#define NOTE_H
#include <QList>
#include "notestate.h"

class Note
{
public:
    Note();
    void appendNoteState(QDateTime timeStamp, QString text, QString title, int cursorPosition);
    QString getText();
    QString getTitle();
private:
    QList<NoteState> noteStateList;
};

#endif // NOTE_H
