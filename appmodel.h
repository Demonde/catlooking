#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include "translator.h"

class AppModel : public QObject
{
    Q_OBJECT
public:
    explicit AppModel(QObject *parent = 0);
    static AppModel* getInstance();

    // Flags
    enum ModelEvent
    {
        UiStateChanged = 0x0,
        TranslationChanged = 0x1
    };
    Q_DECLARE_FLAGS(ModelEvents, ModelEvent)

    enum UiState {
        EditState = 0x0,
        OptionsState = 0x1,
        AboutState = 0x2,
        ExportState = 0x3,
        CloseState = 0x4
    };
    Q_DECLARE_FLAGS(UiStates, UiState)

    UiState getUiState();
    void reportWidgetMouseActive();
    void reportWdigetMouseInactive();
    QString getTranslation(QString elementId);

public slots:
    void closeApplication();

signals:
    void modelWasUpdated(AppModel::ModelEvent);

private:
    AppModel static *instancePointer;
    UiState uiState;
    int activeWidgetCounter;
    Translator *translator;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AppModel::UiStates)
Q_DECLARE_OPERATORS_FOR_FLAGS(AppModel::ModelEvents)

#endif // APPMODEL_H
