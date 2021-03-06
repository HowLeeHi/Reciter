﻿#ifndef RECITER_H
#define RECITER_H

#include <iostream>
#include <vector>
#include "worditem.h"
#include "settings.h"
#include "log.h"
#include "reviewlist.h"
#include <QCoreApplication>
#include <QDir>
using namespace std;


class Reciter
{
public:
    Settings settings;                      //存放设置信息
    string wordlist_address;		        //单词表文件按目标路径
    vector<WordItem> wordlist;              //存放单词，向量内的元素为WordItem类对象
    Log log;                                //用户日志
    ReviewList review;                      //处理复习单词表
    bool reset;                             //是否重置复习计划

    Reciter();
    ~Reciter();
    void run();						        //开始运行背单词软件
    bool is_empty() const                   //判断单词表是否为空
    { return(this->wordlist.size() == 0); }
    void display();					        //显示整个单词表
    int get_size();                         //返回单词的总数目
    void set_address(string wladdr)         //设定单词表文件目标路径
    { this->wordlist_address = wladdr; }
    void create_wordlist();			        //创建一个单词表
    void clear_wordlist();                  //清空一个单词表
    void load_wordlist();			        //打开一个单词表
    bool save_wordlist();			        //保存一个单词表
    void sort_wordlist();			        //整理单词表（从字母a~z排序）
    int add_word();                         //添加一个新单词
    int delete_word(int i);                 //删除第i个WordNode节点，失败则返回值为负数
    int search_word(string word);           //查询功能，打印详情， 返回对应下标
    int test_answer_CN(unsigned int i, unsigned int array[4]);			    //选择汉语解释，返回正误
    int test_answer_ENG(unsigned int i, unsigned int array[4]);			//选择英语解释，返回正误
    void search_Word();                     //模拟查找单词
    bool exam(int testNum, unsigned int *array);                            //模拟考试
    void change_log();                      //更换日志
    void reset_plan();                      //重置单词表计划
    void change_review();                   //更换复习单词表
    bool reset_review();                    //重置复习计划
};


#endif // RECITER_H
