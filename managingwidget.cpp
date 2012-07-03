#include "managingwidget.h"

ManagingWidget::ManagingWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    dayThemeButton(new QPushButton(this)),
    darkThemeButton(new QPushButton(this)),
    exportButton(new QPushButton(this)),
    eraseButton(new QPushButton(this)),
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
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent, ModelInfo *)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent, ModelInfo *)));
    connect(dayThemeButton, SIGNAL(clicked()), appModel, SLOT(switchToDayTheme()));
    connect(darkThemeButton, SIGNAL(clicked()), appModel, SLOT(switchToDarkTheme()));
    connect(exportButton, SIGNAL(clicked()), this, SLOT(askForExport()));
    connect(eraseButton, SIGNAL(clicked()), appModel, SLOT(switchToEraseState()));
    connect(exitButton, SIGNAL(clicked()), appModel, SLOT(closeApplication()));
}

void ManagingWidget::onModelStateChanged(AppModel::ModelEvent modelEvent, ModelInfo * /*infoPointer*/)
{
    if (AppModel::TranslationChanged == modelEvent)
    {
        setTranslations();
    }
}

void ManagingWidget::setupLayouts()
{
    mainLayout->addWidget(dayThemeButton);
    mainLayout->addWidget(darkThemeButton);
    mainLayout->addWidget(exportButton);
    mainLayout->addWidget(eraseButton);
    mainLayout->addWidget(exitButton);

    setLayout(mainLayout);
}

void ManagingWidget::setTranslations()
{
    dayThemeButton->setText(appModel->getTranslation("ManagingWidgetDay"));
    darkThemeButton->setText(appModel->getTranslation("ManagingWidgetNight"));
    exportButton->setText(appModel->getTranslation("ManagingWidgetExport"));
    eraseButton->setText(appModel->getTranslation("ManagingWidgetErase"));
    exitButton->setText(appModel->getTranslation("ManagingWidgetExit"));
}

void ManagingWidget::askForExport()
{
    appModel->exportText(this);
}
