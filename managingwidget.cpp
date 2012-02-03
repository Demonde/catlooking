#include "managingwidget.h"

ManagingWidget::ManagingWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    dayThemeButton(new QPushButton(this)),
    nightThemeButton(new QPushButton(this)),
    exportButton(new QPushButton(this)),
    helpButton(new QPushButton(this)),
    exitButton(new QPushButton(this)),
    mainLayout(new QHBoxLayout()),
    reportOnMouseGoingIn(true)
{
    integrateWithAppModel();
    setTranslations();
    setupLayouts();
    setMouseTracking(true);
}

ManagingWidget::~ManagingWidget()
{
    delete mainLayout;
}

void ManagingWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, const ModelInfo *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, const ModelInfo *)));
    connect(exitButton, SIGNAL(clicked()), appModel, SLOT(closeApplication()));
}


void ManagingWidget::mouseMoveEvent(QMouseEvent */*event*/)
{
    if(reportOnMouseGoingIn)
    {
        emit mouseInsideManagingWidget();
        reportOnMouseGoingIn = false;
    }
}

void ManagingWidget::onModelStateChanged(AppModel::ModelEvent modelEvent, const ModelInfo * /*infoPointer*/)
{
    if (AppModel::TranslationChanged == modelEvent)
    {
        setTranslations();
    }
}

void ManagingWidget::setupLayouts()
{
    mainLayout->addWidget(dayThemeButton);
    mainLayout->addWidget(nightThemeButton);
    mainLayout->addWidget(exportButton);
    mainLayout->addWidget(helpButton);
    mainLayout->addWidget(exitButton);

    setLayout(mainLayout);
}

void ManagingWidget::setTranslations()
{
    dayThemeButton->setText(appModel->getTranslation("ManagingWidgetDay"));
    nightThemeButton->setText(appModel->getTranslation("ManagingWidgetNight"));
    exportButton->setText(appModel->getTranslation("ManagingWidgetExport"));
    helpButton->setText(appModel->getTranslation("ManagingWidgetHelp"));
    exitButton->setText(appModel->getTranslation("ManagingWidgetExit"));
}

void ManagingWidget::reportOnMouseGoingInWidget()
{
    reportOnMouseGoingIn = true;
}
