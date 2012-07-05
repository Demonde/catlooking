#include <QApplication>
#include <QSettings>
#include <QMutex>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QPushButton>
#include "appmodel.h"

AppModel* AppModel::instancePointer(0);
ModelInfo *AppModel::NullPointer(0);

AppModel::AppModel(QObject *parent) :
    QObject(parent),
    uiState(AppModel::OptionsState),
    activeWidgetCounter(0),
    translator(new Translator(this)),
    textWasChangedSinceLastExport(true)
{
    QMutex creationMutex;
    creationMutex.lock();
    if (!instancePointer)
    {
        instancePointer = this;
    }
}

AppModel* AppModel::getInstance()
{
    return instancePointer;
}

void AppModel::closeApplication()
{
    saveText();
    uiState = AppModel::CloseState;
    emit modelWasUpdated(UiStateChanged, NullPointer);
}

void AppModel::switchToDayTheme()
{
    setVisualTheme(AppModel::DayTheme);
}

void AppModel::switchToDarkTheme()
{
    setVisualTheme(AppModel::DarkTheme);
}

AppModel::UiState AppModel::getUiState()
{
    return uiState;
}

void AppModel::reportWidgetMouseActive()
{
    ++activeWidgetCounter;
    if (activeWidgetCounter == 1)
    {
        QApplication::restoreOverrideCursor();
    }
}

void AppModel::reportWdigetMouseInactive()
{
    --activeWidgetCounter;
    if(activeWidgetCounter <= 0)
    {
        activeWidgetCounter = 0;
        QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    }
}

QString AppModel::getTranslation(QString elementId)
{
    return translator->getTranslation(elementId);
}

void AppModel::reportNoteState(QString newNoteText)
{
    noteEditState.text = newNoteText;
    textWasChangedSinceLastExport = true;
    emit modelWasUpdated(AppModel::NoteChanged, &noteEditState);
}

void AppModel::reportSelectionState(QTextCursor newTextCursor)
{
    noteEditState.textCursor = newTextCursor;
    emit modelWasUpdated(AppModel::CursorChanged, &noteEditState);
}

void AppModel::setVisualTheme(UiTheme theme)
{
    if(AppModel::DayTheme == theme)
    {
        emit modelWasUpdated(AppModel::DayThemeEnabled, NULL);
    }
    if(AppModel::DarkTheme == theme)
    {
        emit modelWasUpdated(AppModel::DarkThemeEnabled, NULL);
    }
}

void AppModel::restoreText()
{
    QSettings settings("catlooking.com", "catlooking");
    reportNoteState(settings.value("text").toString());
}

void AppModel::saveText()
{
    QSettings settings("catlooking.com", "catlooking");
    settings.setValue("text", noteEditState.text);
}

void AppModel::exportText(QWidget* parent = NULL)
{
    QString fileName = QFileDialog::getSaveFileName(parent,
                                getInstance()->getTranslation("ExportTextPrompt"),
                                QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                getInstance()->getTranslation("ExportTextFileTypes"));
    if (!fileName.isEmpty())
    {
        if (isFileExists(fileName))
        {
            removeFile(fileName);
        }
        writeDataToTextFile(fileName, noteEditState.text.toUtf8());
        textWasChangedSinceLastExport = false;
    }
    uiState = AppModel::EditState;
    emit modelWasUpdated(UiStateChanged, NullPointer);
}

bool AppModel::isFileExists(QString path)
{
    QFile file;
    file.setFileName(path);
    return file.exists();
}

void AppModel::removeFile(QString path)
{
    QFile file;
    file.setFileName(path);
    if (file.exists())
    {
        setOpenPermissions(path);
        file.remove();
    }
}

void AppModel::writeDataToTextFile(QString path, QByteArray data)
{
    QFile dataFile(path);
    if (dataFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        dataFile.write(data);
    }
}

void AppModel::setOpenPermissions(QString path)
{
    QFile file;
    file.setFileName(path);
    file.setPermissions(QFile::WriteOwner | QFile::WriteUser | QFile::WriteGroup | QFile::WriteOther
                        | QFile::ReadOwner | QFile::ReadUser | QFile::ReadGroup | QFile::ReadOther);
}

void AppModel::clearTextVaraible()
{
    reportNoteState(QString(""));
}

bool AppModel::isTextWasChangedSinceLastExport()
{
    return textWasChangedSinceLastExport && !noteEditState.text.isEmpty();
}

void AppModel::eraseText(QWidget* parent = NULL)
{
    QMessageBox eraseAskMessageBox(parent);

    if(getInstance()->isTextWasChangedSinceLastExport())
    {
        eraseAskMessageBox.setText(getInstance()->getTranslation("EraseTextButtonQuestionWithExportOption"));
    }
    else
    {
        eraseAskMessageBox.setText(getInstance()->getTranslation("EraseTextButtonQuestion"));
    }
    QPushButton *exportTextButton = NULL;
    QPushButton *eraseTextButton;
    if(getInstance()->isTextWasChangedSinceLastExport())
    {
        exportTextButton =
                eraseAskMessageBox.addButton(getInstance()->getTranslation("EraseTextButtonExport"), QMessageBox::ActionRole);
    }
    eraseTextButton =
            eraseAskMessageBox.addButton(getInstance()->getTranslation("EraseTextButtonErase"), QMessageBox::ActionRole);
            eraseAskMessageBox.addButton(getInstance()->getTranslation("EraseTextButtonCancel"), QMessageBox::RejectRole);

    eraseAskMessageBox.exec();
    if (eraseAskMessageBox.clickedButton() == eraseTextButton)
    {
        getInstance()->clearTextVaraible();
    }
    if (getInstance()->isTextWasChangedSinceLastExport() && (eraseAskMessageBox.clickedButton() == exportTextButton))
    {
        getInstance()->exportText(parent);
        if(!getInstance()->isTextWasChangedSinceLastExport())
        {
            getInstance()->clearTextVaraible();
        }
    }
    while(!eraseAskMessageBox.buttons().isEmpty())
    {
        eraseAskMessageBox.removeButton(eraseAskMessageBox.buttons().at(0));
    }

    uiState = AppModel::EditState;
    emit modelWasUpdated(UiStateChanged, NullPointer);
}
