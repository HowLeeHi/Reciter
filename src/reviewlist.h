#ifndef REVIEWLIST_H
#define REVIEWLIST_H

#include <string>
#include <vector>
#include "worditem.h"
#include <direct.h>
#include <QCoreApplication>
#include <QDir>
#include <QDate>
using namespace std;

class ReviewList
{
public:
    string wordlistname;                //复习单词表对应的单词表文件名
    vector<WordItem> reviewlist;        //存放单词，向量内的元素为WordItem类对象

    ReviewList(string wordlistname="null");
    void read();
    void clear();
    void add(WordItem wi);
};

#endif // REVIEWLIST_H
