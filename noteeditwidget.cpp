#include "noteeditwidget.h"

NoteEditWidget::NoteEditWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    plainTextEdit(new QPlainTextEdit(this)),
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
    plainTextEdit->setGeometry(200, 100, width() - 400, height() - 200);
    visualCover->setGeometry(0, 0, width(), height());
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
