#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include "ui_mainwindow.h"

#include <QObject>
#include <QModelIndex>
#include <QDebug>
#include <QStringListModel>
#include <QStringList>
#include <QFile>

class FileObserver : public QObject
{
    Q_OBJECT
public:
    explicit FileObserver(QObject *parent = nullptr);

    FileObserver();
    void addObserver(QString);
    QString getCurrentlyObserved();
    QString getFileContent();

private:
    QStringList fileNames;
    QString currentlyObserved;

};

#endif // FILEOBSERVER_H
