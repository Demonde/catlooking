#ifndef NOTEMODELINFO_H
#define NOTEMODELINFO_H

#include <QTextCursor>
#include "modelinfo.h"

class NoteModelInfo : public ModelInfo
{
public:
    NoteModelInfo() {}
    virtual ~NoteModelInfo() {}
    QString text;
    QTextCursor textCursor;
};

#endif // NOTEMODELINFO_H
