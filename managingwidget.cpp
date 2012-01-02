#include "managingwidget.h"

ManagingWidget::ManagingWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    dayThemeButton(new QPushButton(this)),
    nightThemeButton(new QPushButton(this)),
    exportButton(new QPushButton(this)),
    helpButton(new QPushButton(this)),
    exitButton(new QPushButton(this)),
    mainLayout(new QHBoxLayout())
{
    integrateWithAppModel();
    setTranslations();
    setupLayouts();
}

ManagingWidget::~ManagingWidget()
{
    delete mainLayout;
}

void ManagingWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent)));
    connect(exitButton, SIGNAL(clicked()), appModel, SLOT(closeApplication()));
}

void ManagingWidget::onModelStateChanged(AppModel::ModelEvent modelEvent)
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
