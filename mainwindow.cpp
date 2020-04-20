#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEBUG

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStringListModel(this);
    fileObserver = new FileObserver(this);
    fileswatcher=new QFileSystemWatcher();
    dirswatcher=new QFileSystemWatcher();

#ifdef DEBUG

#endif


    auto stateMachine = new QStateMachine(this);

    auto Startup = new QState(stateMachine);
    auto InFile = new QState(stateMachine);
    auto Backups = new QState(stateMachine);
    auto InBackupList = new QState(stateMachine);
    auto InBackup = new QState(stateMachine);


    Startup->assignProperty(ui->textEdit, "html", "<p align=\"center\">Files in directory:");
    Startup->assignProperty(ui->pushButton, "enabled", false);
    Startup->assignProperty(ui->pushButton_2, "enabled", true);
    Startup->assignProperty(ui->listView, "visible", QVariant(true));
    Startup->assignProperty(ui->textEdit_2, "visible", QVariant(false));
    Startup->assignProperty(ui->listView_2, "visible", QVariant(false));
    Startup->assignProperty(ui->listView_3, "visible", QVariant(false));
    Startup->assignProperty(ui->textEdit_3, "visible", QVariant(false));
    Startup->assignProperty(ui->pushButton_3, "enabled", false);
    Startup->assignProperty(ui->textEdit_4, "enabled", false);
    Startup->assignProperty(ui->pushButton_4, "enabled", false);
    Startup->assignProperty(ui->pushButton_5, "enabled", true);
    Startup->assignProperty(ui->pushButton_6, "enabled", true);

    InFile->assignProperty(ui->textEdit, "html", "<p align=\"center\">Content of the file:");
    InFile->assignProperty(ui->listView, "visible", QVariant(false));
    InFile->assignProperty(ui->pushButton, "enabled", true);
    InFile->assignProperty(ui->pushButton_2, "enabled", true);
    InFile->assignProperty(ui->textEdit_2, "visible", QVariant(true));
    InFile->assignProperty(ui->listView_2, "visible", QVariant(false));
    InFile->assignProperty(ui->listView_3, "visible", QVariant(false));
    InFile->assignProperty(ui->textEdit_2, "enabled", true);
    InFile->assignProperty(ui->textEdit_3, "visible", QVariant(false));
    InFile->assignProperty(ui->pushButton_3, "enabled", true);
    InFile->assignProperty(ui->textEdit_4, "enabled", true);
    InFile->assignProperty(ui->pushButton_4, "enabled", false);
    InFile->assignProperty(ui->pushButton_5, "enabled", false);
    InFile->assignProperty(ui->pushButton_6, "enabled", false);


    Backups->assignProperty(ui->textEdit, "html", "<p align=\"center\">Backuped files:");
    Backups->assignProperty(ui->listView, "visible", QVariant(false));
    Backups->assignProperty(ui->textEdit_2, "visible", QVariant(false));
    Backups->assignProperty(ui->pushButton, "enabled", true);
    Backups->assignProperty(ui->pushButton_2, "enabled", false);
    Backups->assignProperty(ui->listView_2, "visible", QVariant(true));
    Backups->assignProperty(ui->listView_3, "visible", QVariant(false));
    Backups->assignProperty(ui->textEdit_3, "visible", QVariant(false));
    Backups->assignProperty(ui->pushButton_3, "enabled", false);
    Backups->assignProperty(ui->textEdit_4, "enabled", false);
    Backups->assignProperty(ui->pushButton_4, "enabled", false);
    Backups->assignProperty(ui->pushButton_5, "enabled", false);
    Backups->assignProperty(ui->pushButton_6, "enabled", false);


    InBackupList->assignProperty(ui->textEdit, "html", "<p align=\"center\">Avaliable backups:");
    InBackupList->assignProperty(ui->listView, "visible", QVariant(false));
    InBackupList->assignProperty(ui->textEdit_2, "visible", QVariant(false));
    InBackupList->assignProperty(ui->pushButton, "enabled", true);
    InBackupList->assignProperty(ui->pushButton_2, "enabled", true);
    InBackupList->assignProperty(ui->listView_2, "visible", QVariant(false));
    InBackupList->assignProperty(ui->listView_3, "visible", QVariant(true));
    InBackupList->assignProperty(ui->textEdit_3, "visible", QVariant(false));
    InBackupList->assignProperty(ui->pushButton_3, "enabled", false);
    InBackupList->assignProperty(ui->textEdit_4, "enabled", false);
    InBackupList->assignProperty(ui->pushButton_4, "enabled", false);
    InBackupList->assignProperty(ui->pushButton_5, "enabled", false);
    InBackupList->assignProperty(ui->pushButton_6, "enabled", false);


    InBackup->assignProperty(ui->textEdit, "html", "<p align=\"center\">Backup content:");
    InBackup->assignProperty(ui->listView, "visible", QVariant(false));
    InBackup->assignProperty(ui->textEdit_2, "visible", QVariant(false));
    InBackup->assignProperty(ui->pushButton, "enabled", true);
    InBackup->assignProperty(ui->pushButton_2, "enabled", true);
    InBackup->assignProperty(ui->listView_2, "visible", QVariant(false));
    InBackup->assignProperty(ui->listView_3, "visible", QVariant(false));
    InBackup->assignProperty(ui->textEdit_3, "enabled", false);
    InBackup->assignProperty(ui->textEdit_3, "visible", QVariant(true));
    InBackup->assignProperty(ui->pushButton_3, "enabled", false);
    InBackup->assignProperty(ui->textEdit_4, "enabled", false);
    InBackup->assignProperty(ui->pushButton_4, "enabled", true);
    InBackup->assignProperty(ui->pushButton_5, "enabled", false);
    InBackup->assignProperty(ui->pushButton_6, "enabled", false);

    Startup->addTransition(ui->listView, SIGNAL(doubleClicked(QModelIndex)), InFile);
    Startup->addTransition(ui->pushButton_2, SIGNAL(clicked(bool)), Backups);
    Startup->addTransition(ui->pushButton_3, SIGNAL(clicked(bool)), Backups);


    InFile->addTransition(ui->pushButton, SIGNAL(clicked(bool)), Startup);
    InFile->addTransition(ui->pushButton_2, SIGNAL(clicked(bool)), Backups);


    Backups->addTransition(ui->pushButton, SIGNAL(clicked(bool)), Startup);
    Backups->addTransition(ui->listView_2, SIGNAL(doubleClicked(QModelIndex)), InBackupList);


    InBackupList->addTransition(ui->pushButton, SIGNAL(clicked(bool)), Backups);
    InBackupList->addTransition(ui->pushButton_2, SIGNAL(clicked(bool)), Backups);
    InBackupList->addTransition(ui->listView_3, SIGNAL(doubleClicked(QModelIndex)), InBackup);


    InBackup->addTransition(ui->pushButton, SIGNAL(clicked(bool)), InBackupList);
    InBackup->addTransition(ui->pushButton_2, SIGNAL(clicked(bool)), Backups);
    InBackup->addTransition(ui->pushButton_4, SIGNAL(clicked(bool)), InFile);


    model->setStringList(fileNames);
    ui->listView->setModel(model);
    // disable editing
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);


    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addObserver(QModelIndex)));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), SLOT(showBackupFiles()));
    connect(ui->listView_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showFileBackups(QModelIndex)));
    connect(ui->listView_3, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showBackup(QModelIndex)));

    connect(ui->pushButton_3, SIGNAL(clicked(bool)), SLOT(saveYourVersion()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), SLOT(retrieveVersion()));

    connect(ui->textEdit_2, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    connect(ui->pushButton_5,SIGNAL(clicked(bool)),this,SLOT(AddFile()));
    connect(ui->pushButton_6,SIGNAL(clicked(bool)),this,SLOT(AddDirectory()));

    connect(fileswatcher, SIGNAL(fileChanged(QString)), this, SLOT(CheckIfRenamed(QString)));
    connect(dirswatcher, SIGNAL(directoryChanged(QString)), this, SLOT(DirModified(QString)));

    connect(this,SIGNAL(FileAdded(QString)),this,SLOT(onTextChanged(QString)));
    connect(this,SIGNAL(FileWasChanged(QString)),this,SLOT(onTextChanged(QString)));

    stateMachine->setInitialState(Startup);
    stateMachine->start();

}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::addObserver(QModelIndex index)
{
    QStringListModel* listModel = qobject_cast<QStringListModel*>(ui->listView->model());
    QString value = listModel->stringList().at(index.row());
    fileObserver->addObserver(value);
    ui->textEdit_2->setText(fileObserver->getFileContent());
}

void MainWindow::onTextChanged(QString a)
{
    if(!QFile::exists(a))
    qDebug() << a;
    QFile file( a );

    if ( !file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    QString res = in.readAll();

    file.close();

    if( lastBackup == res )
        return;

    lastBackup = res;
    QString desc="";
    QString date = QDateTime::currentDateTime().toString();

    for( int i=0; i<backups.size(); i++ )
    {
        if( backups[i].getFilePath() == a )
        {
            backups[i].addVersionWithDescription(res,date,desc);
            return;
        }
    }

    fileBackup backup;
    backup.setFilePath(a);

    backups.append(backup);
    backups[backups.size()-1].addVersionWithDescription(res,date,desc);

}

void MainWindow::onTextChanged()
{

    QString content = ui->textEdit_2->toPlainText();

    if( content == "Error opening file" ){
        ui->textEdit_2->setReadOnly(true);
        return;
    }
    ui->textEdit_2->setReadOnly(false);
    if( lastBackup == content )
        return;

    lastBackup = content;

    QString filePath = fileObserver->getCurrentlyObserved();
    QString date = QDateTime::currentDateTime().toString();

    // Jeśli zmiana w QT to zmiana w pliku
    QFile file( filePath );
    if( file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        stream << content;
        file.close();
        qDebug() << "Saved";
    }
    QString desc="";
    // Jeśli już operowano na tym pliku to dodaj jego nową wersję
    for( int i=0; i<backups.size(); i++ )
    {
        if( backups[i].getFilePath() == filePath )
        {
            backups[i].addVersionWithDescription(ui->textEdit_2->toPlainText(),date,desc);
            return;
        }
    }

    fileBackup backup;
    backup.setFilePath(filePath);


    backups.append(backup);
    backups[backups.size()-1].addVersionWithDescription(content,date,desc);

}

void MainWindow::showBackupFiles()
{

    QStringListModel * model2 = new QStringListModel(this);
    QStringList backupNames;

    for( int i=0; i<backups.size(); i++ )
        backupNames << backups[i].getFilePath();

    model2->setStringList(backupNames);
    ui->listView_2->setModel(model2);

}

void MainWindow::showFileBackups(QModelIndex index)
{
    QStringListModel* listModel = qobject_cast<QStringListModel*>(ui->listView_2->model());
    QString value = listModel->stringList().at(index.row());

    QStringListModel * model3 = new QStringListModel(this);
    QStringList avaliableBackups;

    QVector<QString> fileVersions;
    QVector<QString> versionDates;
    QVector<QString> descriptionData;

    for( int i=0; i<backups.size(); i++ )
    {
        if( backups[i].getFilePath() == value )
        {
            fileVersions = backups[i].getFileVersions();
            versionDates = backups[i].getVersionDates();
            descriptionData = backups[i].getVersionDescription();

            backupNo = i;
            break;
        }
    }

    for( int i=0; (i<fileVersions.size() && i<versionDates.size()); i++ )
        avaliableBackups << QString::number(i+1) + ". Backup Date: " + versionDates[i]+" desc: "+descriptionData[i];

    model3->setStringList(avaliableBackups);
    ui->listView_3->setModel(model3);

}

void MainWindow::showBackup(QModelIndex index)
{

    QStringListModel* listModel = qobject_cast<QStringListModel*>(ui->listView_3->model());
    QString value = listModel->stringList().at(index.row());

    QString num;

    for( int i=0; value.at(i) != '.'; i++ )
        num += value.at(i);

    int no = num.toInt()-1;
    QVector<QString> back = backups[backupNo].getFileVersions();
    QString backupText = back[no];
    toRetrieve = back[no];

    ui->textEdit_3->setText(backupText);

}

void MainWindow::saveYourVersion()
{
    QString description = ui->textEdit_4->toPlainText(); // wczytuje z pola
    ui->textEdit_4->clear();    // czyści pole
    qDebug()<<description;
    QString content = ui->textEdit_2->toPlainText(); // Wczytuje zawartosc wersji pliku

    QString filePath = fileObserver->getCurrentlyObserved();
    QString date = QDateTime::currentDateTime().toString();
    //int no=0;

    for( int i=0; i<backups.size(); i++ )
    {
        if( backups[i].getFilePath() == filePath )
        {
            backups[i].addVersionWithDescription(content,date, description);
            return;
        }
    }


    fileBackup BackupDescription;
    BackupDescription.setFilePath(filePath);

    backups.append(BackupDescription);
    backups[backups.size()-1].addVersionWithDescription(content, date,  description);
}

void MainWindow::retrieveVersion()
{
   ui->textEdit_2->setText(toRetrieve);
}

void MainWindow::AddDirectory()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(path.isNull())
    {
        qDebug()<<"getExistingDirectory failed";
        return;
    }
    if(dirs.keys().contains(path))
        return;
    dirswatcher->addPath(path);
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList fileList=dir.entryInfoList();
    QStringList sList;
    for(int i=0;i<fileList.size();++i)
        sList<<fileList.at(i).filePath();
    dirs.insert(path,sList);
    int Flag=0;
    for(int i=0;i<sList.size();++i)
    {
       if(files_paths.contains(sList.at(i)))
       {
           Flag=1;
           //fileNames.removeOne(sList.at(i));
           files_paths.removeOne(sList.at(i));
           continue;
       }
       fileswatcher->addPath(sList.at(i));
       emit(FileAdded(sList.at(i)));
       fileNames.append(sList.at(i));
    }
    model->setStringList(fileNames);
    ui->listView->setModel(model);
    if(Flag)
        helper.remove(path);
}

void MainWindow::DirModified(QString path)
{
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList fileList=dir.entryInfoList();

    QStringList newList;
    for(int i=0;i<fileList.size();++i)
        newList<<fileList.at(i).filePath();
    QStringList oldList=dirs[path];
    QSet<QString> substract;
    if(oldList.size()> newList.size())
    {
        substract=oldList.toSet().subtract(newList.toSet());
        QStringList s= substract.toList();
        for(int j=0;j<substract.size();++j)
        {
            fileswatcher->removePath(s.at(j));
            fileNames.removeOne(s.at(j));
            dirs[path].removeOne(s.at(j));
        }
    }
    else if(oldList.size()< newList.size())
    {
        substract=newList.toSet().subtract(oldList.toSet());
        QStringList s= substract.toList();
        for(int j=0;j<substract.size();++j)
        {
            dirs[path].append(s.at(j));
            fileswatcher->addPath(s.at(j));
            fileNames.append(s.at(j));
            emit(FileAdded(s.at(j)));
        }
    }
    model->setStringList(fileNames);
    ui->listView->setModel(model);
}
void MainWindow::AddFile()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Select Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(path.isNull())
    {
        qDebug()<<"getExistingDirectory failed";
        return;
    }
    if(dirs.keys().contains(path))
        return;
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList infolist=dir.entryInfoList();
    QStringList slist;
    for(int i=0;i<infolist.size();++i)
        slist<<(infolist.at(i).filePath());
    this->helper.insert(path,slist);

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setDirectory(path);
    dialog.setFilter(QDir::Files);
    dialog.setWindowTitle("Open File");
    dialog.setNameFilter("ALL(*);;Text files(*.txt)");
    dialog.exec();
    QStringList selected_files = dialog.selectedFiles();
    for(int i=0;i<selected_files.size();++i)
    {
        QString file=selected_files.at(i);
        if( !files_paths.contains(file))
         {
             files_paths.append(file);
             fileNames.append(file);
             fileswatcher->addPath(file);
             model->setStringList(fileNames);
             ui->listView->setModel(model); 
             emit(FileAdded(file));
         }
         else
             qDebug()<<"File is already monitored\n";
    }
}

void MainWindow::CheckIfRenamed(QString s)
{
    if(QFile::exists(s))
        emit(FileWasChanged(s));
    else if(files_paths.contains(s))
    {
       QFileInfo info(s);
       QDir directory=info.dir();

       QDir dir(directory.path());
       dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

       QFileInfoList newFileList=dir.entryInfoList();
       QStringList newList;
       for(int i=0;i<newFileList.size();++i)
           newList<<newFileList.at(i).filePath();

       QStringList oldList =helper[directory.path()];
       QString new_renamed=nullptr;
       if(oldList.size()!=newList.size())
       {
           fileNames.removeOne(s);
           files_paths.removeOne(s);
           fileswatcher->removePath(s);
           model->setStringList(fileNames);
           ui->listView->setModel(model);
           helper[directory.path()].removeOne(s);
           return;
       }
       for(int i=0;i<newList.size();++i)
       {
          if(!oldList.contains(newList.at(i)))
          {
              new_renamed=newList.at(i);
              helper[directory.path()].removeOne(s);
              helper[directory.path()].append(new_renamed);
              fileswatcher->removePath(s);
              fileswatcher->addPath(new_renamed);
              fileNames.removeOne(s);
              fileNames.append(new_renamed);
              files_paths.removeOne(s);
              files_paths.append(new_renamed);
              model->setStringList(fileNames);
              ui->listView->setModel(model);
              return;
          }
       }
    }
    else {
        QFileInfo info(s);
        QDir directory=info.dir();

        QDir dir(directory.path());
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

        QFileInfoList newFileList=dir.entryInfoList();
        QStringList newList;
        for(int i=0;i<newFileList.size();++i)
            newList<<newFileList.at(i).filePath();

        QStringList oldList =dirs[directory.path()];
        QString new_renamed=nullptr;
        for(int i=0;i<newList.size();++i)
        {
           if(!oldList.contains(newList.at(i)))
           {
               new_renamed=newList.at(i);
               dirs[directory.path()].removeOne(s);
               dirs[directory.path()].append(new_renamed);
               fileswatcher->removePath(s);
               fileswatcher->addPath(new_renamed);
               fileNames.append(new_renamed);
               fileNames.removeOne(s);
               model->setStringList(fileNames);
               ui->listView->setModel(model);
               return;
           }
        }
    }
}
