#include "noteeditwidget.h"
#include <QFont>
#include <QFontMetrics>
#include <QTextBlock>
#include <QDebug> // debug

const int NoteEditWidget::TextEditVerticalMargin(100);
const QString NoteEditWidget::CiceroTextSample("Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium");
const int NoteEditWidget::LineHeightPercentage(122);
const float NoteEditWidget::NoteEditWidthMultiplier(0.875);

NoteEditWidget::NoteEditWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    textEdit(new QTextEdit(this)),
    visualCover(new QFrame(this))
{
    integrateWithAppModel();
    setupVisualCover();
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(reportNoteState()));
    connect(textEdit, SIGNAL(selectionChanged()), this, SLOT(reportSelectionState()));
    connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(reportSelectionState()));
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void NoteEditWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, ModelInfo *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, ModelInfo *)));
}

void NoteEditWidget::setFocus()
{
    textEdit->setFocus();
}

void NoteEditWidget::resizeEvent(QResizeEvent *)
{
    noteEditHeight = height() - TextEditVerticalMargin;
    noteEditWidth = static_cast<int>(NoteEditWidthMultiplier * noteEditHeight);
    noteEditXPos = (width() - noteEditWidth) / 2;
    noteEditYPos = (height() - noteEditHeight) / 2;

    visualCover->setGeometry(0, 0, width(), height());
    textEdit->setGeometry(noteEditXPos, noteEditYPos, noteEditWidth, noteEditHeight);
    textEdit->setFocus();
    textEdit->setFont(getFontForTextEditWith(noteEditWidth));

    for (QTextBlock block = textEdit->document()->begin(); block.isValid(); block = block.next())
    {
        QTextCursor tc = QTextCursor(block);
        QTextBlockFormat fmt = block.blockFormat();
        fmt.setLineHeight(LineHeightPercentage, QTextBlockFormat::ProportionalHeight);
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
        adjustTextEditPosition();
    }
    if (AppModel::CursorChanged == modelEvent)
    {
        NoteModelInfo* newInfo = dynamic_cast<NoteModelInfo*>(infoPointer);
        if (newInfo)
        {
            textEdit->setTextCursor(newInfo->textCursor);
        }
        resetTextEditPosition();
    }
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

const QFont NoteEditWidget::getFontForTextEditWith(const int width)
{
    int textEditWidth(0);
    int fontSize(2);
    QFont font("Designosaur", fontSize, QFont::Normal, true);
    while (textEditWidth < width)
    {
        font.setPointSize(fontSize);
        QFontMetrics fm(font);
        textEditWidth = fm.width(CiceroTextSample);
        ++fontSize;
    }
    font.setPointSize(fontSize - 1);
    return font;
}

void NoteEditWidget::adjustTextEditPosition()
{
    if(textEdit->cursorRect().y() <= textEdit->size().height())
    {
        int adjustedNoteEditYPos = (noteEditHeight / 2) - textEdit->cursorRect().y();
        textEdit->setGeometry(noteEditXPos, adjustedNoteEditYPos, noteEditWidth, noteEditHeight);
    }
}

void NoteEditWidget::resetTextEditPosition()
{
    textEdit->setGeometry(noteEditXPos, noteEditYPos, noteEditWidth, noteEditHeight);
}
