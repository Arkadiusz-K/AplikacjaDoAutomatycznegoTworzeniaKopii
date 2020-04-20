#include "filebackup.h"

void fileBackup::addVersion(QString text, QString date)
{
    fileVersions.append(text);
    versionDates.append(date);
}

void fileBackup::addVersionWithDescription(QString text, QString date, QString description)
{
    fileVersions.append(text);
    versionDates.append(date);
    descriptionData.append(description);
}

QString fileBackup::getFilePath()
{
    return filePath;
}

QVector<QString> fileBackup::getFileVersions()
{
    return fileVersions;
}

QVector<QString> fileBackup::getVersionDates()
{
    return versionDates;
}

QVector<QString> fileBackup::getVersionDescription()
{
    return descriptionData;
}

void fileBackup::setFilePath(QString path)
{
    filePath = path;
}
