#ifndef FILEBACKUP_H
#define FILEBACKUP_H

#include <QString>
#include <QVector>

class fileBackup
{

public:

    void addVersion(QString, QString); // Funkcja deprecjonowana
    void addVersionWithDescription(QString, QString, QString);
    QString getFilePath();
    QVector<QString> getFileVersions();
    QVector<QString> getVersionDates();
    QVector<QString> getVersionDescription();
    void setFilePath(QString);


private:
    QString filePath;
    QVector<QString> fileVersions;
    QVector<QString> versionDates;
    QVector<QString> descriptionData;


};

#endif // FILEBACKUP_H
