#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->index = 0;
    ui->stackedWidget->setCurrentIndex(0);
    ui->wordListName->setText(QString::fromStdString(this->reciter.settings.filename_record));
}

MainWindow::~MainWindow()
{
    delete ui;
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

    if(file_name.isEmpty())
    {
        this->reciter.set_address("null.txt");
        ui->wordListName->setText("null");

        this->reciter.settings.filename_record = "null";
        this->reciter.settings.filepath_record = "./null.txt";
        this->reciter.settings.write();
    }
    else
    {
        this->reciter.set_address(file_full.toStdString());
        ui->wordListName->setText(file_name.remove(".txt"));

        this->reciter.settings.filename_record = file_name.toStdString();
        this->reciter.settings.filepath_record = file_path.toStdString();
        this->reciter.settings.write();
    }

    this->reciter.load_wordlist();
}

void MainWindow::on_goStudy_clicked()
{
    QTextCodec *codec=QTextCodec::codecForName("GB2312");

    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(0);

    if(this->index>=this->reciter.wordlist.size())
    {
        ui->stackedWidget_2->setCurrentIndex(2);
    }
    else
    {
        ui->GoStudy_newWord->setText(QString::fromStdString(this->reciter.wordlist[this->index].word));
        ui->GoStudy_newWord->adjustSize();

        ui->GoStudy_word->setText(QString::fromStdString(this->reciter.wordlist[this->index].word));
        ui->GoStudy_word->adjustSize();

        ui->GoStudy_partOfSpeech->setText(QString::fromStdString(this->reciter.wordlist[this->index].part_of_speech));
        ui->GoStudy_partOfSpeech->adjustSize();

        ui->GoStudy_meaning->setText(codec->toUnicode(this->reciter.wordlist[this->index].meaning.c_str()));
        ui->GoStudy_meaning->adjustSize();

        ui->GoStudy_example->setText(QString::fromStdString(this->reciter.wordlist[this->index].example));
        ui->GoStudy_example->adjustSize();

        ui->GoStudy_exampleMeaning->setText(codec->toUnicode(this->reciter.wordlist[this->index].example_meaning.c_str()));
        ui->GoStudy_exampleMeaning->adjustSize();
    }
}



void MainWindow::on_GoStudy_back_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     this->index = 0;
     ui->stackedWidget_2->setCurrentIndex(0);
}



void MainWindow::on_GoStudy_unknow_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_GoStudy_next_clicked()
{
    if(++(this->index)>=this->reciter.wordlist.size())
    {
        ui->stackedWidget_2->setCurrentIndex(2);
    }
    else
    {
        QTextCodec *codec=QTextCodec::codecForName("GB2312");

        ui->stackedWidget_2->setCurrentIndex(0);

        ui->GoStudy_newWord->setText(QString::fromStdString(this->reciter.wordlist[this->index].word));
        ui->GoStudy_newWord->adjustSize();

        ui->GoStudy_word->setText(QString::fromStdString(this->reciter.wordlist[this->index].word));
        ui->GoStudy_word->adjustSize();

        ui->GoStudy_partOfSpeech->setText(QString::fromStdString(this->reciter.wordlist[this->index].part_of_speech));
        ui->GoStudy_partOfSpeech->adjustSize();

        ui->GoStudy_meaning->setText(codec->toUnicode(this->reciter.wordlist[this->index].meaning.c_str()));
        ui->GoStudy_meaning->adjustSize();

        ui->GoStudy_example->setText(QString::fromStdString(this->reciter.wordlist[this->index].example));
        ui->GoStudy_example->adjustSize();

        ui->GoStudy_exampleMeaning->setText(codec->toUnicode(this->reciter.wordlist[this->index].example_meaning.c_str()));
        ui->GoStudy_exampleMeaning->adjustSize();
    }
}

void MainWindow::on_GoStudy_know_clicked()
{
    if(++(this->index)>=this->reciter.wordlist.size())
    {
        ui->stackedWidget_2->setCurrentIndex(2);
    }
    else
    {
        QTextCodec *codec=QTextCodec::codecForName("GB2312");

        ui->stackedWidget_2->setCurrentIndex(0);

        ui->GoStudy_newWord->setText(QString::fromStdString(this->reciter.wordlist[this->index].word));
        ui->GoStudy_newWord->adjustSize();

        ui->GoStudy_word->setText(QString::fromStdString(this->reciter.wordlist[this->index].word));
        ui->GoStudy_word->adjustSize();

        ui->GoStudy_partOfSpeech->setText(QString::fromStdString(this->reciter.wordlist[this->index].part_of_speech));
        ui->GoStudy_partOfSpeech->adjustSize();

        ui->GoStudy_meaning->setText(codec->toUnicode(this->reciter.wordlist[this->index].meaning.c_str()));
        ui->GoStudy_meaning->adjustSize();

        ui->GoStudy_example->setText(QString::fromStdString(this->reciter.wordlist[this->index].example));
        ui->GoStudy_example->adjustSize();

        ui->GoStudy_exampleMeaning->setText(codec->toUnicode(this->reciter.wordlist[this->index].example_meaning.c_str()));
        ui->GoStudy_exampleMeaning->adjustSize();
    }
}

void MainWindow::on_Schedule_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_changePlan_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_reviewAndTest_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_ReviewAndTest_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->index = 0;
}



void MainWindow::on_test_confirm_button_released()
{
    ui->stackedWidget_3->setCurrentIndex(1);

}
