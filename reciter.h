#ifndef RECITER_H
#define RECITER_H

#include <iostream>
#include <vector>
#include "worditem.h"
#include "settings.h"
using namespace std;


class Reciter
{
public:
    Settings settings;                      //存放设置信息
    string wordlist_address;		        //单词表文件按目标路径
    vector<WordItem> wordlist;              //存放单词，向量内的元素为WordItem类对象

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
    bool test_answer_CN(int i);			    //选择汉语解释，返回正误
    bool test_answer_ENG(int i);			//选择英语解释，返回正误
    void search_Word();                     //模拟查找单词
    void exam();                            //模拟考试
};


#endif // RECITER_H
