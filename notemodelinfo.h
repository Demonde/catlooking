#ifndef NOTEMODELINFO_H
#define NOTEMODELINFO_H
#include "modelinfo.h"

class NoteModelInfo : public ModelInfo
{
public:
    NoteModelInfo() : text(""), textCursorPosition(0) {}
    virtual ~NoteModelInfo() {}
    QString text;
    int textCursorPosition;
};

#endif // NOTEMODELINFO_H
