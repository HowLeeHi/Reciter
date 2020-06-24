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
        this->reciter.settings.filepath_record = "./";
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
    ui->test_title->setText("本考试共有10个题，全部为选择题，每题1分。选择你认为正确的答案，点击确认开始考试。");

    ui->test_title->setWordWrap(true);
    ui->test_title->setAlignment(Qt::AlignTop);
}

void MainWindow::on_ReviewAndTest_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->index = 0;
}



void MainWindow::on_test_confirm_button_released()
{
    if(!this->reciter.exam(testnum, index_testNum)){
        ui->test_title->setText("单词表为空，请重新添加");
        ui->test_title->adjustSize();
        return;
    }else{
        ui->test_title->setText("本考试共有10个题，全部为选择题，每题1分。选择你认为正确的答案，点击确认开始考试。");
        ui->test_title->setWordWrap(true);
        ui->test_title->setAlignment(Qt::AlignTop);
    }
    //跳转到题目界面，初始化分数和题目
    ui->test_title->adjustSize();
    ui->stackedWidget_3->setCurrentIndex(1);
    this->scores = 0;
    this->n = 0;

    //显示第一题题面
    this->ans = reciter.test_answer_CN(index_testNum[n], index_options);
    QTextCodec *codec=QTextCodec::codecForName("GB2312");
    ui->question->setText(QString::fromStdString(this->reciter.wordlist[this->index_testNum[n]].getEnglish()));
    ui->Button_A->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[0]].getChinese().c_str()));
    ui->Button_B->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[1]].getChinese().c_str()));
    ui->Button_C->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[2]].getChinese().c_str()));
    ui->Button_D->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[3]].getChinese().c_str()));
    n++;
}


void MainWindow::on_test_next_released()
{
    if(n < this->testnum){
        //更新题面.英译汉
        this->ans = reciter.test_answer_CN(index_testNum[n], index_options);
        QTextCodec *codec=QTextCodec::codecForName("GB2312");
        ui->question->setText(QString::fromStdString(this->reciter.wordlist[this->index_testNum[n]].getEnglish()));
        ui->question->adjustSize();
        ui->Button_A->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[0]].getChinese().c_str()));
        ui->Button_B->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[1]].getChinese().c_str()));
        ui->Button_C->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[2]].getChinese().c_str()));
        ui->Button_D->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[3]].getChinese().c_str()));
        ui->Button_A->adjustSize();
        ui->Button_B->adjustSize();
        ui->Button_C->adjustSize();
        ui->Button_D->adjustSize();
        n++;
    } else {
        ui->stackedWidget_3->setCurrentIndex(2);
        if(scores < testnum * 0.6){
            ui->grade->setText("您只得了              分><, 尚需努力！");
            ui->grade1->setNum(scores);
           }
           else if((scores >= testnum * 0.6) && (scores < testnum * 0.85)){
            ui->grade->setText("您得了              分， 及格颇有余，优秀尚不足，加油！");
            ui->grade1->setNum(scores);
           }
           else if((scores >= testnum * 0.85) && (scores < testnum)){
            ui->grade->setText("您得了              分， 非常优秀，加油！");
            ui->grade1->setNum(scores);
           }
           else if(scores == testnum){
            ui->grade->setText("您得了满分！");
           }
    }
}

void MainWindow::on_Button_A_released()
{
    if(ans==0){
        this->scores++;
    }
}
void MainWindow::on_Button_B_released()
{
    if(ans==1){
        this->scores++;
    }
}
void MainWindow::on_Button_C_released()
{
    if(ans==2){
        this->scores++;
    }
}
void MainWindow::on_Button_D_released()
{
    if(ans==3){
        this->scores++;
    }
}
