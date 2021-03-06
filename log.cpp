﻿#include "log.h"

Log::Log(string wordlistname)
{
    this->wordlistname = wordlistname;
    this->read();
}

Log::~Log()
{
}

void Log::read()
{
    ifstream fin(QCoreApplication::applicationDirPath().toStdString()+"/log/log_"+this->wordlistname+".txt");
    string buff;

    if(fin)
    {
        fin >> this->index_recordOfGoStudy;
        fin >> buff;
        this->startDate = QDate::fromString(QString::fromStdString(buff),"yyyy/M/d");
        fin >> buff;
        this->deadline = QDate::fromString(QString::fromStdString(buff),"yyyy/M/d");
        fin >> this->daysNum;
        fin >> buff;
        this->lastPlan = QDate::fromString(QString::fromStdString(buff),"yyyy/M/d");
        fin >> this->newWordNum;
        fin >> this->reviewNum;
        fin >> this->doneWordNum;
    }
    else    //如果缺少必要的文件系统，就自动创建
    {
        this->index_recordOfGoStudy = 0;
        this->startDate = QDate::currentDate();
        this->deadline = QDate::currentDate();
        this->daysNum = startDate.daysTo(deadline);
        this->lastPlan = QDate::fromString("2000/1/1","yyyy/M/d");
        this->generate_plan(0);

        QDir dir;
        if(!dir.exists(QCoreApplication::applicationDirPath()+"/log"))
            dir.mkdir(QCoreApplication::applicationDirPath()+"/log");

        this->write();
    }
}

void Log::write()
{
    ofstream fout(QCoreApplication::applicationDirPath().toStdString()+"/log/log_"+this->wordlistname+".txt");

    fout << this->index_recordOfGoStudy << endl
         << this->startDate.toString("yyyy/M/d").toStdString() << endl
         << this->deadline.toString("yyyy/M/d").toStdString() << endl
         << this->daysNum << endl
         << this->lastPlan.toString("yyyy/M/d").toStdString() << endl
         << this->newWordNum << endl
         << this->reviewNum << endl
         << this->doneWordNum << endl;

}

void Log::change_wordlistname(string newwordlistname)
{
    this->write();
    this->wordlistname = newwordlistname;
    this->read();
}

void Log::generate_plan(unsigned int wordlistSize) //检查今天是否已经计划，如果没有就制定计划
{
    if(this->lastPlan != QDate::currentDate())
    {
        if(this->deadline <= QDate::currentDate())
        {
            this->newWordNum = wordlistSize - this->index_recordOfGoStudy;
            this->reviewNum = 3*this->newWordNum;
            this->doneWordNum = 0;

            //每日复习数超过单词总数，这是不允许的
            if(this->reviewNum > wordlistSize)
                this->reviewNum = wordlistSize;
        }
        else
        {
            this->newWordNum = (wordlistSize - this->index_recordOfGoStudy)/QDate::currentDate().daysTo(this->deadline);
            this->reviewNum = 3*this->newWordNum;
            this->doneWordNum = 0;

            //天数太多导致每日学词数为0，这是不允许的
            if((this->newWordNum==0)&&(((wordlistSize - this->index_recordOfGoStudy)%QDate::currentDate().daysTo(this->deadline))!=0))
                this->newWordNum = 1;

            //天数太多导致每日复习数为0，这是不允许的
            if((this->reviewNum==0)&&((wordlistSize%QDate::currentDate().daysTo(this->deadline))!=0))
                this->reviewNum = 1;

            //每日复习数超过单词总数，这是不允许的
            if(this->reviewNum > wordlistSize)
                this->reviewNum = wordlistSize;
        }
        this->lastPlan = QDate::currentDate();
    }
}

void Log::change_plan(unsigned int wordlistSize) //如果用户手动修改了计划，使用这个更新
{
    if(this->deadline <= QDate::currentDate())
    {
        this->newWordNum = wordlistSize - this->index_recordOfGoStudy;
        this->reviewNum = 3*this->newWordNum;
        this->doneWordNum = 0;

        //每日复习数超过单词总数，这是不允许的
        if(this->reviewNum > wordlistSize)
            this->reviewNum = wordlistSize;
    }
    else
    {
        this->newWordNum = (wordlistSize - this->index_recordOfGoStudy)/QDate::currentDate().daysTo(this->deadline);
        this->reviewNum = 3*this->newWordNum;
        this->doneWordNum = 0;

        //天数太多导致每日学词数为0，这是不允许的
        if((this->newWordNum==0)&&(((wordlistSize - this->index_recordOfGoStudy)%QDate::currentDate().daysTo(this->deadline))!=0))
            this->newWordNum = 1;

        //天数太多导致每日复习数为0，这是不允许的
        if((this->reviewNum==0)&&((wordlistSize%QDate::currentDate().daysTo(this->deadline))!=0))
            this->reviewNum = 1;

        //每日复习数超过单词总数，这是不允许的
        if(this->reviewNum > wordlistSize)
            this->reviewNum = wordlistSize;
    }
    this->lastPlan = QDate::currentDate();

    this->daysNum = startDate.daysTo(deadline);
}

void Log::reset_plan(unsigned int wordlistSize)
{
    this->index_recordOfGoStudy = 0;
    this->startDate = QDate::currentDate();
    this->deadline = QDate::currentDate();
    this->daysNum = startDate.daysTo(deadline);
    this->lastPlan = QDate::fromString("2000/1/1","yyyy/M/d");
    this->generate_plan(wordlistSize);
}
