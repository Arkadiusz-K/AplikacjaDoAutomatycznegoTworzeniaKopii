#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QStringListModel>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QObject>
#include <QVector>
#include <QDate>
#include <QFileSystemWatcher>

#include "filebackup.h"
#include "fileobserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Holding the paths to observed files
    QStringList fileNames;
    // Model to display paths in modelview
    QStringListModel *model;
    FileObserver *fileObserver;
    QVector<fileBackup> backups;
    QVector<fileBackup> backupswithdesc;
    QVector<QFileSystemWatcher*> watchers;
    QString lastBackup;
    QString toRetrieve;
    int backupNo;

    QMap<QString,QStringList> dirs;    //directory=> files in directories
    QMap<QString,QStringList> helper;  //For Add File option, stores image of directory to get the new name if file was renamed
    QStringList files_paths;
    QFileSystemWatcher* fileswatcher;
    QFileSystemWatcher* dirswatcher;

signals:
    void added(QString value);
    void FileAdded(QString a);
    void FileWasChanged(QString s);
public slots:
    void addObserver(QModelIndex index);
    void showFileBackups(QModelIndex index);
    void showBackup(QModelIndex index);
    void onTextChanged(QString a);
    void onTextChanged();
    void showBackupFiles();

    void saveYourVersion();
    void retrieveVersion();

    void AddFile();
    void AddDirectory();
    void CheckIfRenamed(QString s);
    void DirModified(QString path);

};

#endif // MAINWINDOW_H
