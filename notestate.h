#ifndef NOTESTATE_H
#define NOTESTATE_H

#include <QDateTime>
#include <QString>

class NoteState
{
public:
    NoteState(QDateTime timeStamp, QString text, QString title, int cursorPosition);
    QDateTime getTimeStamp() const;
    QString getText() const;
    QString getTitle() const;
    int getCursorPosition() const;
    bool operator< (const NoteState &rvalue) const {return timeStamp < rvalue.timeStamp;}

private:
    QDateTime timeStamp;
    QString text;
    QString title;
    int cursorPosition;
};


#endif // NOTESTATE_H
