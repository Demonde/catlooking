#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QLocale>
#include <QMap>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QObject *parent = 0);
    QString getTranslation(QString elementId);

private:
    QLocale currentLocale;
    QLocale defaultLocale;
    QMap<QString, QString> translationMap;
    QString getFileNameCountrySpecificTranslation(QLocale locale);
    QString getFileNameGeneralTranslation(QLocale locale);
    bool translationExists(QLocale locale);
    QString getTranslationFileName(QLocale locale);
    void loadTranslation(QLocale locale);
};

#endif // TRANSLATOR_H
