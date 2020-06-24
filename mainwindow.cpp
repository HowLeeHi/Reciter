﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->index = this->reciter.log.index_recordOfGoStudy;
    ui->stackedWidget->setCurrentIndex(0);

    ui->wordListName->setText(QString::fromStdString(this->reciter.settings.filename_record));

    QPushButton *pSearchButton = ui->pushButton;
    pSearchButton->setCursor(Qt::PointingHandCursor);
//    pSearchButton->setFixedSize(22, 22);
    pSearchButton->setToolTip(QStringLiteral("搜索"));
    QMargins margins = ui->search_line->textMargins();
    ui->search_line->setTextMargins(margins.left(), margins.top(), pSearchButton->width(), margins.bottom());
    ui->search_line->setPlaceholderText(QStringLiteral("请输入搜索内容"));

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(pSearchButton);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    ui->search_line->setLayout(pSearchLayout);
    connect(pSearchButton, SIGNAL(clicked(bool)), this, SLOT(search()));
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

    this->reciter.update_log();
}

void MainWindow::on_goStudy_clicked()
{
    QTextCodec *codec=QTextCodec::codecForName("GB2312");

    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(0);

    if(this->index>=this->reciter.wordlist.size())
    {
        ui->stackedWidget_2->setCurrentIndex(3);
    }
    else if(this->index>=this->reciter.log.index_recordOfGoStudy+this->reciter.log.newWordNum)
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
     this->reciter.log.index_recordOfGoStudy = this->index;
     this->reciter.log.write();
     ui->stackedWidget_2->setCurrentIndex(0);

     ui->wordListName->setText(QString::fromStdString(this->reciter.settings.filename_record));

     ui->wordsNum->setText(QString::number(this->reciter.log.newWordNum));
     ui->wordsNum->adjustSize();

     ui->listDone->setText(QString::number(this->reciter.log.index_recordOfGoStudy));
     ui->listDone->adjustSize();

     ui->listSize->setText("/"+QString::number(this->reciter.wordlist.size()));
     ui->listSize->adjustSize();

     ui->daysLeft->setText(QString::number(QDate::currentDate().daysTo(this->reciter.log.deadline)));
     ui->daysLeft->adjustSize();

     ui->dayMax->setText("/"+QString::number(this->reciter.log.daysNum));
     ui->dayMax->adjustSize();
}



void MainWindow::on_GoStudy_unknow_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_GoStudy_next_clicked()
{
    this->reciter.log.newWordNum--;
    if(++(this->index)>=this->reciter.wordlist.size())
    {
        ui->stackedWidget_2->setCurrentIndex(3);
    }
    else if((this->index)>=(this->index+this->reciter.log.newWordNum))
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
    this->reciter.log.newWordNum--;
    if(++(this->index)>=this->reciter.wordlist.size())
    {
        ui->stackedWidget_2->setCurrentIndex(3);
    }
    else if((this->index)>=(this->index+this->reciter.log.newWordNum))
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
    this->reciter.log.read();

    ui->wordListName->setText(QString::fromStdString(this->reciter.settings.filename_record));

    ui->wordsNum->setText(QString::number(this->reciter.log.newWordNum));
    ui->wordsNum->adjustSize();

    ui->listDone->setText(QString::number(this->reciter.log.index_recordOfGoStudy));
    ui->listDone->adjustSize();

    ui->listSize->setText("/"+QString::number(this->reciter.wordlist.size()));
    ui->listSize->adjustSize();

    ui->daysLeft->setText(QString::number(QDate::currentDate().daysTo(this->reciter.log.deadline)));
    ui->daysLeft->adjustSize();

    ui->dayMax->setText("/"+QString::number(this->reciter.log.daysNum));
    ui->dayMax->adjustSize();
}

void MainWindow::on_changePlan_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

    ui->Schedule_startDate->setText(this->reciter.log.startDate.toString("yyyy/M/d"));
    ui->Schedule_startDate->adjustSize();

    ui->dateEdit->setDate(this->reciter.log.deadline);

    ui->Schedule_daysNum->setText(QString::number(this->reciter.log.daysNum));
    ui->Schedule_daysNum->adjustSize();

    ui->Schedule_newWordNum->setText(QString::number(this->reciter.log.newWordNum));
    ui->Schedule_newWordNum->adjustSize();

    ui->Schedule_reviewNum->setText(QString::number(this->reciter.log.reviewNum));
    ui->Schedule_reviewNum->adjustSize();
}

void MainWindow::on_reviewAndTest_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_3->setCurrentIndex(0);
    QString text = "本考试共有";
    if(testnum >= 10){
        text.append(testnum/10 +'0');
        text.append(testnum%10 + '0');
    } else {
        text.append(testnum +'0');
    }
    text.append("个题，全部为选择题，每题1分。选择你认为正确的答案，点击确认开始考试。");
    ui->test_title->setText(text);
    ui->test_title->setWordWrap(true);
    ui->test_title->setAlignment(Qt::AlignTop);
}

void MainWindow::on_ReviewAndTest_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->index = 0;

    ui->wordListName->setText(QString::fromStdString(this->reciter.settings.filename_record));

    ui->wordsNum->setText(QString::number(this->reciter.log.newWordNum));
    ui->wordsNum->adjustSize();

    ui->listDone->setText(QString::number(this->reciter.log.index_recordOfGoStudy));
    ui->listDone->adjustSize();

    ui->listSize->setText("/"+QString::number(this->reciter.wordlist.size()));
    ui->listSize->adjustSize();

    ui->daysLeft->setText(QString::number(QDate::currentDate().daysTo(this->reciter.log.deadline)));
    ui->daysLeft->adjustSize();

    ui->dayMax->setText("/"+QString::number(this->reciter.log.daysNum));
    ui->dayMax->adjustSize();
}



void MainWindow::on_test_confirm_button_released()
{
    if(!this->reciter.exam(testnum, index_testNum)){
        ui->test_title->setText("单词表为空，请重新添加");
        ui->test_title->adjustSize();
        return;
    }else{
        QString text = "本考试共有";
        if(testnum >= 10){
            text.append(testnum/10 +'0');
            text.append(testnum%10 + '0');
        } else {
            text.append(testnum +'0');
        }
        text.append("个题，全部为选择题，每题1分。选择你认为正确的答案，点击确认开始考试。");
        ui->test_title->setText(text);
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
    if(exam_flag == true){
        ui->question->setText(QString::fromStdString(this->reciter.wordlist[this->index_testNum[n]].getEnglish()));
        ui->Button_A->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[0]].getChinese().c_str()));
        ui->Button_B->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[1]].getChinese().c_str()));
        ui->Button_C->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[2]].getChinese().c_str()));
        ui->Button_D->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[3]].getChinese().c_str()));
        //调整大小
//        ui->question->setWordWrap(true);
//        ui->question->setAlignment(Qt::AlignTop);
    } else {
        ui->question->setText(codec->toUnicode(this->reciter.wordlist[this->index_testNum[n]].getChinese().c_str()));
        ui->Button_A->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[0]].getEnglish()));
        ui->Button_B->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[1]].getEnglish()));
        ui->Button_C->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[2]].getEnglish()));
        ui->Button_D->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[3]].getEnglish()));
        ui->question->setWordWrap(true);
        ui->question->setAlignment(Qt::AlignTop);
    }
    n++;
}


void MainWindow::on_test_next_released()
{
    if(n < this->testnum){
        //更新题面.英译汉
        this->ans = reciter.test_answer_CN(index_testNum[n], index_options);
        QTextCodec *codec=QTextCodec::codecForName("GB2312");
        if(exam_flag == true){
            ui->question->setText(QString::fromStdString(this->reciter.wordlist[this->index_testNum[n]].getEnglish()));
            ui->Button_A->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[0]].getChinese().c_str()));
            ui->Button_B->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[1]].getChinese().c_str()));
            ui->Button_C->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[2]].getChinese().c_str()));
            ui->Button_D->setText(codec->toUnicode(this->reciter.wordlist[this->index_options[3]].getChinese().c_str()));
            ui->question->setWordWrap(true);
            ui->question->setAlignment(Qt::AlignTop);
        } else {
            ui->question->setText(codec->toUnicode(this->reciter.wordlist[this->index_testNum[n]].getChinese().c_str()));
            ui->Button_A->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[0]].getEnglish()));
            ui->Button_B->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[1]].getEnglish()));
            ui->Button_C->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[2]].getEnglish()));
            ui->Button_D->setText(QString::fromStdString(this->reciter.wordlist[this->index_options[3]].getEnglish()));
//            ui->question->setWordWrap(true);
//            ui->question->setAlignment(Qt::AlignTop);
        }
        n++;
    } else {
        //考试结果
        ui->stackedWidget_3->setCurrentIndex(2);
        if(scores < testnum * 0.6){
            QString text = "您只得了 ";
            text.append(scores+'0');
            text.append(" 分><, 尚需努力！");
            ui->grade->setText(text);
        } else if((scores >= testnum * 0.6) && (scores < testnum * 0.85)){
            QString text = "您得了 ";
            text.append(scores+'0');
            text.append(" 分， 及格颇有余，优秀尚不足，加油！");
            ui->grade->setText(text);
        } else if((scores >= testnum * 0.85) && (scores < testnum)){
            QString text = "您得了 ";
            text.append(scores+'0');
            text.append(" 分， 非常优秀，加油！");
            ui->grade->setText(text);
        } else if(scores == testnum){
            ui->grade->setText("您得了满分！");
        }
        ui->grade->setWordWrap(true);
        ui->grade->setAlignment(Qt::AlignTop);
    }
}

//定义分数变化
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

//定义考试类型
void MainWindow::on_En_Zh_clicked()
{
    this->exam_flag = true;
}

void MainWindow::on_Zh_En_clicked()
{
    this->exam_flag = false;
}
void MainWindow::search()
{
    QString strText = ui->search_line->text();
    if (!strText.isEmpty())
    {
        QTextCodec *codec=QTextCodec::codecForName("GB2312");
        string Text = strText.toStdString();
        int pos = this->reciter.search_word(Text);
        if(pos > -1){
            QString re = QString::fromStdString(this->reciter.wordlist[pos].getEnglish());
            QString re1 = QString::fromStdString(this->reciter.wordlist[pos].part_of_speech);
            QString re2 = codec->toUnicode(this->reciter.wordlist[pos].meaning.c_str());
            QString re3 = QString::fromStdString(this->reciter.wordlist[pos].example);
            QString re4 = codec->toUnicode(this->reciter.wordlist[pos].example_meaning.c_str());
            QMessageBox::information(this, QStringLiteral("搜索"), QStringLiteral("搜索结果为：\n"
                         "拼写：%1\n"
                         "词性：%2\n"
                         "释义：%3\n"
                         "例句：%4\n"
                         "例句翻译：%5")
                                     .arg(re).arg(re1).arg(re2).arg(re3).arg(re4));
        } else {
            QMessageBox::information(this, QStringLiteral("搜索"), QStringLiteral("搜索结果为：\n单词表内不存在该单词"));
        }
    }
}

