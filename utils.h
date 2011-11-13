#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include "exception.h"

class Utils : public QObject
{
    Q_OBJECT

public:
    explicit Utils(QObject *parent = 0);
    static void installFont(QString resourceFilePath);
    static QString getFileMd5Hash(QString path);
    static bool isFileExists(QString path);
    static void removeFile(QString destination);
    static void writeDataToTextFile(QString path, QByteArray data);

private:
    static const QString TempDirForFonts;
    static void addApplicationFont(QString path);

    static void ensureDirectoryExistence(QString path);
    static void ensureFileExistense(QString resourcePath, QString path);
    static QString getDirectoryNameFromPath(QString path);
    static QString getFileNameFromPath(QString path);

    static void copyFile(QString source, QString destination);
    static QString getMd5Hash(QString path);
    static bool isFilesEqualsByMd5(QString firstFilePath, QString secondFilePath);

    static void setOpenPermissions(QString path);


public:
    class UtilsException : public Exception
    {
    public:
        UtilsException(const char * message)
            :Exception(message){}
    };

};

#endif // UTILS_H
