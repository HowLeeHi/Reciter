#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog.h"

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

}

void MainWindow::on_changeList_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("选择"),
            "./",
            tr("textfile(*.txt)"));
}
