#include "note.h"

Note::Note()
{
}

void Note::appendNoteState(QDateTime timeStamp, QString text, QString title, int cursorPosition)
{
    noteStateList.append(NoteState(timeStamp, text, title, cursorPosition));
}

QString Note::getText()
{
    qSort(noteStateList);
    return noteStateList.last().getText();
}

QString Note::getTitle()
{
    qSort(noteStateList);
    return noteStateList.last().getTitle();
}
