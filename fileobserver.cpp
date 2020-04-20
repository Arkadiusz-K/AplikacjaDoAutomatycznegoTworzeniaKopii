#include "fileobserver.h"

FileObserver::FileObserver(QObject *parent) : QObject (parent)
{

}
FileObserver::FileObserver()
{

}

void FileObserver::addObserver(QString path)
{
    currentlyObserved = path;
    if( FileObserver::fileNames.contains(path) )
        qDebug() << "File with path: " << path << " is already observed.";
    else
    {
        fileNames << path;
        qDebug() << "Added observer for path: " << path;
    }
}

QString FileObserver::getCurrentlyObserved()
{

    return currentlyObserved;

}

QString FileObserver::getFileContent()
{

    qDebug() << "Trying to open: " << currentlyObserved;

    QFile file(currentlyObserved);

    if ( !file.open(QIODevice::ReadOnly))
        return "Error opening file";

    QTextStream in(&file);
    QString res = in.readAll();

    file.close();

    return res;

}
