#include "noteeditwidget.h"
#include <QTextBlock> // debug
#include <QDebug> // debug

const int NoteEditWidget::textEditVerticalMargin(80);

NoteEditWidget::NoteEditWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    textEdit(new QTextEdit(this)),
    visualCover(new QFrame(this))
//    noteStateReporter(new QTimer(this))
{
    integrateWithAppModel();
    setupVisualCover();
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(reportNoteState()));
    connect(textEdit, SIGNAL(selectionChanged()), this, SLOT(reportSelectionState()));
//    connect(noteStateReporter, SIGNAL(timeout()), this, SLOT(reportNoteState()));
//    noteStateReporter->setInterval(500);
//    noteStateReporter->start();
}

void NoteEditWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, ModelInfo *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, ModelInfo *)));
}

void NoteEditWidget::resizeEvent(QResizeEvent *)
{
    visualCover->setGeometry(0, 0, width(), height());
    textEdit->setGeometry(200, 100, width() - 400, height() - 200);
    textEdit->setFocus();
    for (QTextBlock block = textEdit->document()->begin(); block.isValid(); block = block.next())
    {
        QTextCursor tc = QTextCursor(block);
        QTextBlockFormat fmt = block.blockFormat();
        fmt.setLineHeight(200, QTextBlockFormat::ProportionalHeight);
        tc.setBlockFormat(fmt);
    }
}

void NoteEditWidget::onModelStateChanged(AppModel::ModelEvent modelEvent, ModelInfo * infoPointer)
{
    if (AppModel::NoteChanged == modelEvent)
    {
        NoteModelInfo* newInfo = dynamic_cast<NoteModelInfo*>(infoPointer);
        if ((newInfo) && (textEdit->toPlainText() != newInfo->text))
        {
            textEdit->setPlainText(newInfo->text);
        }
    }
    if (AppModel::CursorChanged == modelEvent)
    {
        NoteModelInfo* newInfo = dynamic_cast<NoteModelInfo*>(infoPointer);
        if (newInfo)
        {
            textEdit->setTextCursor(newInfo->textCursor);
        }
    }
//    if (AppModel::CursorChanged == modelEvent)
//    {
//        NoteModelInfo* newInfo = dynamic_cast<NoteModelInfo*>(infoPointer);
//        if (newInfo)
//        {
//            textEdit->setTextCursor(newInfo->textCursor);
//        }
//    }
}

void NoteEditWidget::reportNoteState()
{
    appModel->reportNoteState(textEdit->toPlainText());
}

void NoteEditWidget::reportSelectionState()
{
    appModel->reportSelectionState(textEdit->textCursor());
}

void NoteEditWidget::setupVisualCover()
{
    visualCover->setObjectName("visualCover");
    visualCover->setAttribute(Qt::WA_TransparentForMouseEvents);
    visualCover->setFocusPolicy(Qt::NoFocus);
    visualCover->raise();
}
