#include "utils.h"
#include <QDir>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>
#include <QRegExp>
#include <QCryptographicHash>
#include <QProcess>
#include <QUrl>
#include <iostream>

const QString Utils::TempDirForFonts = "fonts/";

Utils::Utils(QObject *parent) :
    QObject(parent)
{
}

void Utils::installFont(QString resourceFilePath)
{
    try
    {
        QDir fonstDir;
        fonstDir.setPath("./");
        fonstDir.mkpath(TempDirForFonts);
        QString localFilePath = TempDirForFonts + getFileNameFromPath(resourceFilePath);
        ensureFileExistense(resourceFilePath, localFilePath);
        addApplicationFont(localFilePath);
    }
    catch (UtilsException& exception)
    {
        std::cerr << exception.what();
    }
}

void Utils::ensureFileExistense(QString resourcePath, QString destinationPath)
{
    QFile destinationFile, resourceFile;
    destinationFile.setFileName(destinationPath);
    resourceFile.setFileName(resourcePath);
    if (!resourceFile.exists())
    {
        throw UtilsException(QString("[Utils] Can't find " + resourcePath + " in resource.\n").toAscii());
    }

    if (!isFilesEqualsByMd5(resourcePath, destinationPath))
    {
        copyFile(resourcePath, destinationPath);
    }
}

QString Utils::getFileNameFromPath(QString path)
{
    QString fileName;
    QRegExp fileNameRegExp("([^/]+)$");
    if (fileNameRegExp.indexIn(path, 0) != -1)
    {
        fileName = fileNameRegExp.cap(1);
    }
    else
    {
        throw UtilsException(QString("[Utils] Can't get filename from path " + path).toAscii());
    }
    return fileName;
}

QString Utils::getDirectoryNameFromPath(QString path)
{
    QString directoryName;
    QRegExp directoryNameRegExp("(.+)/([^/]*)$");
    if (directoryNameRegExp.indexIn(path, 0) != -1)
    {
        directoryName = directoryNameRegExp.cap(1);
    }
    else
    {
        throw UtilsException(QString("[Utils] Can't get directory name from path " + path).toAscii());
    }
    return directoryName;
}

void Utils::addApplicationFont(QString path)
{
    if (-1 == QFontDatabase::addApplicationFont(path))
    {
        throw UtilsException(QString("[Utils] Can't install font from " + path).toAscii());
    }
}

void Utils::copyFile(QString source, QString destination)
{
    removeFile(destination);
    ensureDirectoryExistence(getDirectoryNameFromPath(destination));
    bool copySuccess = false;
    copySuccess = QFile::copy(source, destination);
    if (!copySuccess)
    {
        throw UtilsException(QString("[Utils] Can't copy from " + source + " to " + destination + "\n").toAscii());
    }
    setOpenPermissions(destination);
}

void Utils::setOpenPermissions(QString path)
{
    QFile file;
    file.setFileName(path);
    bool setPermissionSuccess = false;
    setPermissionSuccess = file.setPermissions(QFile::WriteOwner | QFile::WriteUser | QFile::WriteGroup | QFile::WriteOther
                        | QFile::ReadOwner | QFile::ReadUser | QFile::ReadGroup | QFile::ReadOther);
    if (!setPermissionSuccess)
    {
        throw UtilsException(QString("[Utils] Can't set open permissions for  " + path + "\n").toAscii());
    }
}

void Utils::ensureDirectoryExistence(QString path)
{
    QDir directory;
    bool creationSuccessful = directory.mkpath(path);
    if (!creationSuccessful)
    {
        throw UtilsException(QString("[Utils] Can't create directory for ensurance " + path + "\n").toAscii());
    }
}

bool Utils::isFilesEqualsByMd5(QString firstFilePath, QString secondFilePath)
{
    bool equals = false;
    try
    {
        equals = (getMd5Hash(firstFilePath) == getMd5Hash(secondFilePath));
    }
    catch (UtilsException& exception)
    {
        std::cerr << exception.what();
    }
    return equals;
}

QString Utils::getMd5Hash(QString path)
{
    QFile dataFile(path);
    QString md5Hash;
    if (dataFile.open(QIODevice::ReadOnly))
    {
        md5Hash = QCryptographicHash::hash(dataFile.readAll(), QCryptographicHash::Md5).toHex();
    }
    else
    {
        throw UtilsException(QString("[Utils] Can't open " + path + " for md5 computing\n").toAscii());
    }
    return md5Hash;
}

QString Utils::getFileMd5Hash(QString path)
{
    QFile dataFile(path);
    QString md5Hash;
    if (dataFile.open(QIODevice::ReadOnly))
    {
        md5Hash = QCryptographicHash::hash(dataFile.readAll(), QCryptographicHash::Md5).toHex();
    }
    return md5Hash;
}

bool Utils::isFileExists(QString path)
{
    QFile file;
    file.setFileName(path);
    return file.exists();
}

void Utils::removeFile(QString path)
{
    QFile file;
    file.setFileName(path);
    if (file.exists())
    {
        setOpenPermissions(path);
        file.remove();
    }
}

void Utils::writeDataToTextFile(QString path, QByteArray data)
{
    QFile dataFile(path);
    if (dataFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        dataFile.write(data);
    }
    else
    {
        qCritical() << "[Utils] Can't open text file for write" << path;
    }
}
