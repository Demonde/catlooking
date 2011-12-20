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
    dayThemeButton->setText("day");
    nightThemeButton->setText("night");
    exportButton->setText("export");
    helpButton->setText("help");
    exitButton->setText("exit");
    titleLabel->setText("Title");
}
