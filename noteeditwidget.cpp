#include "noteeditwidget.h"
#include <QFile> // debug

NoteEditWidget::NoteEditWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    textEdit(new QTextEdit(this)),
    visualCover(new QFrame(this))
{
    integrateWithAppModel();
    setupVisualCover();
}

void NoteEditWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, const void *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, const void *)));
}

void NoteEditWidget::resizeEvent(QResizeEvent *)
{
    visualCover->setGeometry(0, 0, width(), height());
    textEdit->setGeometry(200, 100, width() - 400, height() - 200);
    // debug
    QFile htmlFile("/home/sychev/base/catlooking-build/text.html");
    if (htmlFile.open(QIODevice::ReadOnly))
    {
        textEdit->setHtml(htmlFile.readAll());
    }
}

void NoteEditWidget::onModelStateChanged(AppModel::ModelEvent, const void * /*dataPointer*/)
{
}

void NoteEditWidget::setupVisualCover()
{
    visualCover->setObjectName("visualCover");
    visualCover->setAttribute(Qt::WA_TransparentForMouseEvents);
    visualCover->setFocusPolicy(Qt::NoFocus);
    visualCover->raise();
}
