#include "noteeditwidget.h"
#include <QFile> // debug
#include <QTextBlock> // debug

const int NoteEditWidget::textEditVerticalMargin(80);

NoteEditWidget::NoteEditWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    textEdit(new QTextEdit(this)),
    visualCover(new QFrame(this))
{
    integrateWithAppModel();
    setupVisualCover();
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void NoteEditWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, const ModelInfo *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, const ModelInfo *)));
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

void NoteEditWidget::onModelStateChanged(AppModel::ModelEvent modelEvent, const ModelInfo * infoPointer)
{
    if (AppModel::NoteChanged == modelEvent)
    {
        NoteModelInfo* newInfo = dynamic_cast<NoteModelInfo*>(infoPointer);
        if (newInfo)
        {
            textEdit->setPlainText(newInfo->text);
            QTextCursor textCursor = textEdit->textCursor();
            textCursor.setPosition(newInfo->textCursorPosition);
            textEdit->setTextCursor(textCursor);
            // todo: recalculate geometry
        }
    }
}

void NoteEditWidget::onTextChanged()
{
    appModel->reportNoteWasChanged(textEdit->toPlainText(), textEdit->textCursor().position());
}

void NoteEditWidget::setupVisualCover()
{
    visualCover->setObjectName("visualCover");
    visualCover->setAttribute(Qt::WA_TransparentForMouseEvents);
    visualCover->setFocusPolicy(Qt::NoFocus);
    visualCover->raise();
}
