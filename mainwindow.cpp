#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton * btn = new QPushButton;
    btn->setParent(this);
    btn->resize(100,28);
    btn->setText("Firstbutton");
    btn->move(100,100);
    setFixedSize(400,640);
    setWindowTitle("Reciter");

    connect(btn,&QPushButton::clicked,this,&QWidget::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
