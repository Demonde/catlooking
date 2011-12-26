#include "managingwidget.h"

ManagingWidget::ManagingWidget(QWidget *parent) :
    QFrame(parent),
    appModel(AppModel::getInstance()),
    dayThemeButton(new QPushButton(this)),
    nightThemeButton(new QPushButton(this)),
    exportButton(new QPushButton(this)),
    helpButton(new QPushButton(this)),
    exitButton(new QPushButton(this)),
    titleLabel(new QLabel(this)),
    titleLineEdit(new QLineEdit(this)),
    mainLayout(new QVBoxLayout()),
    topButtonsLayout(new QHBoxLayout()),
    titleLayout(new QHBoxLayout())
{
    setTranslations();
    setupLayouts();
    integrateWithAppModel();
    connect(titleLineEdit, SIGNAL(cursorPositionChanged(int,int)),
            this, SIGNAL(managingWidgetActivityEvent()));
    connect(exitButton, SIGNAL(clicked()), appModel, SLOT(closeApplication()));
}

ManagingWidget::~ManagingWidget()
{
    delete mainLayout;
    delete topButtonsLayout;
    delete titleLayout;
}

void ManagingWidget::integrateWithAppModel()
{
    connect(appModel, SIGNAL(modelWasUpdated(AppModel::ModelEvent)),
            this, SLOT(onModelStateChanged(AppModel::ModelEvent)));
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
    topButtonsLayout->addWidget(dayThemeButton);
    topButtonsLayout->addWidget(nightThemeButton);
    topButtonsLayout->addWidget(exportButton);
    topButtonsLayout->addWidget(helpButton);
    topButtonsLayout->addWidget(exitButton);

    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleLineEdit);

    mainLayout->addLayout(topButtonsLayout);
    mainLayout->addLayout(titleLayout);
    setLayout(mainLayout);
}

void ManagingWidget::setTranslations()
{
    dayThemeButton->setText(appModel->getTranslation("ManagingWidgetDay"));
    nightThemeButton->setText(appModel->getTranslation("ManagingWidgetNight"));
    exportButton->setText(appModel->getTranslation("ManagingWidgetExport"));
    helpButton->setText(appModel->getTranslation("ManagingWidgetHelp"));
    exitButton->setText(appModel->getTranslation("ManagingWidgetExit"));
    titleLabel->setText(appModel->getTranslation("ManagingWidgetTitle"));
}

void ManagingWidget::clearFocusFromTitleEdit()
{
    titleLineEdit->clearFocus();
}
