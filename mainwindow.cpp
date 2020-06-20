#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_goStudy_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_changeList_clicked()    //手动选择文件
{
    QString file_full, file_name, file_path;
    QFileInfo fi;
    file_full = QFileDialog::getOpenFileName(this,
                                             tr("选择"),
                                             "./",
                                             tr("textfile(*.txt)"));
    fi = QFileInfo(file_full);
    file_name = fi.fileName();
    file_path = fi.absolutePath();

    this->reciter.set_address(file_name.toStdString());
    this->reciter.load_wordlist();
    ui->wordListName->setText(file_name.remove(".txt"));
}

void MainWindow::on_reviewAndTest_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_GoStudy_back_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_GoStudy_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
