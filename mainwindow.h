#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//access to the file system modelof the OS
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

public slots:
    void copyToClipboard();
    void showDetails();


private:
    Ui::MainWindow *ui;
    QFileSystemModel *m_model;
};
#endif // MAINWINDOW_H
