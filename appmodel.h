#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include "translator.h"
#include "notemodelinfo.h"

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
        TranslationChanged = 0x1,
        NoteChanged = 0x2,
        CursorChanged = 0x3,
        DayThemeEnabled = 0x4,
        DarkThemeEnabled = 0x5
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

    enum UiTheme {
        DayTheme = 0x0,
        DarkTheme = 0x1
    };
    Q_DECLARE_FLAGS(UiThemes, UiTheme)

    UiState getUiState();
    void reportWidgetMouseActive();
    void reportWdigetMouseInactive();
    QString getTranslation(QString elementId);
    void reportNoteState(QString newNoteText);
    void reportSelectionState(QTextCursor newTextCursor);
    void setVisualTheme(UiTheme theme);

public slots:
    void closeApplication();
    void switchToDayTheme();
    void switchToDarkTheme();

signals:
    void modelWasUpdated(AppModel::ModelEvent, ModelInfo *);

private:
    AppModel static *instancePointer;
    UiState uiState;
    int activeWidgetCounter;
    Translator *translator;
    static ModelInfo *NullPointer;
    NoteModelInfo noteEditState;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AppModel::UiStates)
Q_DECLARE_OPERATORS_FOR_FLAGS(AppModel::ModelEvents)
Q_DECLARE_OPERATORS_FOR_FLAGS(AppModel::UiThemes)

#endif // APPMODEL_H
