#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include "translator.h"

Translator::Translator(QObject *parent) :
    QObject(parent),
    currentLocale(QLocale::system()),
    defaultLocale(QLocale(QLocale::English, QLocale::UnitedStates))
{
    if(translationExists(currentLocale))
    {
        loadTranslation(currentLocale);
    }
    else
    {
        loadTranslation(defaultLocale);
    }
}

QString Translator::getTranslation(QString elementId)
{
    if (translationMap.contains(elementId))
    {
        return translationMap.value(elementId);
    }
    else
    {
        return QString();
    }
}

bool Translator::translationExists(QLocale locale)
{
    // file with name like English.UnitedStates.lang
    QFile translationFile(getFileNameCountrySpecificTranslation(locale));
    if (translationFile.exists())
    {
        return true;
    }
    // file with name like English.lang
    translationFile.setFileName(getFileNameGeneralTranslation(locale));
    if (translationFile.exists())
    {
        return true;
    }
    // we didn't find appropriate lang file
    return false;
}

QString Translator::getTranslationFileName(QLocale locale)
{
    // file with name like English.UnitedStates.lang
    QFile translationFile(getFileNameCountrySpecificTranslation(locale));
    if (translationFile.exists())
    {
        return getFileNameCountrySpecificTranslation(locale);
    }
    // file with name like English.lang
    translationFile.setFileName(getFileNameGeneralTranslation(locale));
    if (translationFile.exists())
    {
        return getFileNameGeneralTranslation(locale);
    }
    // we didn't find appropriate lang file
    return QString();
}

QString Translator::getFileNameCountrySpecificTranslation(QLocale locale)
{
    return ":/translations/resources/translations/"
            + locale.languageToString(locale.language()) + "."
            + locale.countryToString(locale.country()) + ".lang";
}

QString Translator::getFileNameGeneralTranslation(QLocale locale)
{
    return ":/translations/resources/translations/"
            + locale.languageToString(locale.language()) + ".lang";
}

void Translator::loadTranslation(QLocale locale)
{
    QFile xmlFile;
    xmlFile.setFileName(getTranslationFileName(locale));
    if (xmlFile.open(QIODevice::ReadOnly))
    {
        QDomDocument domDocument;
        QString errorStr;
        int errorLine;
        int errorColumn;
        if (!domDocument.setContent(&xmlFile, true, &errorStr, &errorLine,
                             &errorColumn)) {
            qWarning() << "Error of translation xml file"
                    << getTranslationFileName(locale) << errorLine << errorColumn << errorStr;
        }
        QDomElement root = domDocument.documentElement();
        if (root.tagName() != "translation") {
            qWarning() << "Root element is not <translation>";
        }
        // Reading the translations
        QDomElement child = root.firstChildElement();
        while (!child.isNull()) {
            if ((child.tagName() == "item")
                    && (child.hasAttribute("id"))
                    && (!child.attribute("id").isEmpty()))
            {
                translationMap.insert(child.attribute("id"), child.text());
            }
            child = child.nextSiblingElement();
        }
    }
}

