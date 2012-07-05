#include "noteeditwidget.h"
#include <QFont>
#include <QFontMetrics>
#include <QTextBlock>

const int NoteEditWidget::TextEditVerticalMargin(100);
const QString NoteEditWidget::CiceroTextSample("Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium");
const int NoteEditWidget::LineHeightPercentage(122);
const float NoteEditWidget::NoteEditWidthMultiplier(0.875);
const int NoteEditWidget::TextEditAnimationDuration(400);
const int NoteEditWidget::TextEditTextCursorCaretDeadZone(7);

NoteEditWidget::NoteEditWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    textEdit(new QTextEdit(this)),
    visualCover(new QFrame(this)),
    textEditAnimation(new QPropertyAnimation(textEdit, "geometry"))
{
    integrateWithAppModel();
    setupVisualCover();
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(reportNoteState()));
    connect(textEdit, SIGNAL(selectionChanged()), this, SLOT(reportSelectionState()));
    connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(reportSelectionState()));
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEditAnimation->setDuration(TextEditAnimationDuration);
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
        if (!textEdit->hasFocus() && newInfo && (textEdit->toPlainText() != newInfo->text))
        {
            textEdit->setPlainText(newInfo->text);
            resetTextEditPosition();
        }
    }
    if (AppModel::CursorChanged == modelEvent)
    {
        NoteModelInfo* newInfo = dynamic_cast<NoteModelInfo*>(infoPointer);
        if(!textEdit->hasFocus() && newInfo)
        {
            textEdit->setTextCursor(newInfo->textCursor);
        }
        resetTextEditPosition();
    }
}

void NoteEditWidget::reportNoteState()
{
    if(textEdit->hasFocus())
    {
        appModel->reportNoteState(textEdit->toPlainText());
        appModel->reportSelectionState(textEdit->textCursor());
        adjustTextEditPosition();
    }
}

void NoteEditWidget::reportSelectionState()
{
    if(textEdit->hasFocus())
    {
        appModel->reportSelectionState(textEdit->textCursor());
    }
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
    QFont font("Arial", fontSize, QFont::Bold, true);
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
    textEditAnimation->stop();
    if((textEdit->cursorRect().y() <= (textEdit->size().height()) - textEdit->font().pixelSize() * 2))
    {
        int adjustedNoteEditYPos;
        if (textEdit->cursorRect().left() > TextEditTextCursorCaretDeadZone)
        {
            adjustedNoteEditYPos = (noteEditHeight / 2) - textEdit->cursorRect().bottom();
        }
        else
        {
            adjustedNoteEditYPos = textEdit->y();
        }
        textEditAnimation->setEndValue(QRect(noteEditXPos, adjustedNoteEditYPos, noteEditWidth, noteEditHeight));
        textEditAnimation->start();
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
}

void NoteEditWidget::resetTextEditPosition()
{
    textEditAnimation->stop();
    textEditAnimation->setEndValue(QRect(noteEditXPos, noteEditYPos, noteEditWidth, noteEditHeight));
    textEditAnimation->start();
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}
