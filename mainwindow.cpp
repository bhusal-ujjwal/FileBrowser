#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_model = new QFileSystemModel(this);
    m_model->setRootPath(QDir::currentPath());

    ui->treeView->setModel(m_model);
    ui->listView->setModel(m_model);


    //set riclick enabled and access to be shown in menu
    ui->listView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *actDetails = new QAction("Show Details");
    ui->listView->addAction(actDetails);

    QAction *actClip = new QAction("Copy to Clipboard");
    ui->listView->addAction(actClip);

    connect(actDetails,&QAction::triggered, this, &MainWindow::showDetails);
    connect(actClip,&QAction::triggered, this, &MainWindow::copyToClipboard);



    connect(ui->treeView,&QTreeView::clicked, ui->listView,&QListView::setRootIndex);
    connect(ui->treeView,&QTreeView::clicked,[&](const QModelIndex &i){

        QString path = m_model->filePath(i);
        ui->teHistory->append(path);

    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

//clipboard function
void MainWindow::copyToClipboard(){
    qApp->clipboard()->setText(m_model->filePath(ui->listView->currentIndex()));

}

//show details function
void MainWindow::showDetails(){
    QFileInfo info = m_model->fileInfo(ui->listView->currentIndex());
    QMessageBox::information(this,"File Browser",
                             tr("File Info: \n"
                                "File name: %1\n"
                                "File size: %2\n"
                                "Is Directory: %3").arg(info.fileName()).arg(info.size()).arg(info.isDir()?"true":"false")
                             );

}



//opening path and saving the url of the file directory
void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "File Browser","");
    ui->lePath->setText(path);

    //here we load the tree and list view where we select the url in browse button
    QModelIndex index = m_model->index(path);
    ui->treeView->setCurrentIndex(index);
    ui->listView->setRootIndex(index);

}

