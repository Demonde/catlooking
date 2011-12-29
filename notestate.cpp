#include "notestate.h"

NoteState::NoteState(QDateTime timeStamp, QString text, QString title, int cursorPosition) :
    timeStamp(timeStamp),
    text(text),
    title(title),
    cursorPosition(cursorPosition)
{
}

QDateTime NoteState::getTimeStamp() const
{
    return timeStamp;
}

QString NoteState::getText() const
{
    return text;
}

QString NoteState::getTitle() const
{
    return title;
}

int NoteState::getCursorPosition() const
{
    return cursorPosition;
}
