#include "reviewlist.h"
#include <QDebug>
#include <QString>

ReviewList::ReviewList(string wordlistname)
{
    this->wordlistname = wordlistname;
    this->read();
}

void ReviewList::read()
{
    QDir dir;
    if(!dir.exists(QCoreApplication::applicationDirPath()+"/review/"))
        dir.mkdir(QCoreApplication::applicationDirPath()+"/review/");
    if(!dir.exists(QCoreApplication::applicationDirPath()+"/review/"+QString::fromStdString(this->wordlistname)))
        dir.mkdir(QCoreApplication::applicationDirPath()+"/review/"+QString::fromStdString(this->wordlistname));

    WordItem wi;
    ifstream fin(QCoreApplication::applicationDirPath().toStdString()+
                 "/review/"+
                 this->wordlistname+
                 "/"+
                 QDate::currentDate().toString("yyyy_M_d").toStdString()+
                 ".txt");
    this->reviewlist.clear();
    while (fin >> wi){
        this->reviewlist.push_back(wi);
    }
}

void ReviewList::clear()
{
    vector<WordItem> clear;
    this->reviewlist.swap(clear);
}

void ReviewList::add(WordItem wi)   //根据艾宾浩斯记忆曲线制定复习计划
{
    QDir dir;
    if(!dir.exists(QCoreApplication::applicationDirPath()+"/review/"+QString::fromStdString(this->wordlistname)))
        dir.mkdir(QCoreApplication::applicationDirPath()+"/review/"+QString::fromStdString(this->wordlistname));

    ofstream fout;

    //添加到1天后的复习列表
    fout.open(QCoreApplication::applicationDirPath().toStdString()+
              "/review/"+
              this->wordlistname+
              "/"+
              QDate::currentDate().addDays(1).toString("yyyy_M_d").toStdString()+
              ".txt",
              ios::app);
    fout << wi;
    fout.close();

    //添加到2天后的复习列表
    fout.open(QCoreApplication::applicationDirPath().toStdString()+
              "/review/"+
              this->wordlistname+
              "/"+
              QDate::currentDate().addDays(2).toString("yyyy_M_d").toStdString()+
              ".txt",
              ios::app);
    fout << wi;
    fout.close();

    //添加到4天后的复习列表
    fout.open(QCoreApplication::applicationDirPath().toStdString()+
              "/review/"+
              this->wordlistname+
              "/"+
              QDate::currentDate().addDays(4).toString("yyyy_M_d").toStdString()+
              ".txt",
              ios::app);
    fout << wi;
    fout.close();

    //添加到7天后的复习列表
    fout.open(QCoreApplication::applicationDirPath().toStdString()+
              "/review/"+
              this->wordlistname+
              "/"+
              QDate::currentDate().addDays(7).toString("yyyy_M_d").toStdString()+
              ".txt",
              ios::app);
    fout << wi;
    fout.close();

    //添加到15天后的复习列表
    fout.open(QCoreApplication::applicationDirPath().toStdString()+
              "/review/"+
              this->wordlistname+
              "/"+
              QDate::currentDate().addDays(15).toString("yyyy_M_d").toStdString()+
              ".txt",
              ios::app);
    fout << wi;
    fout.close();
}
