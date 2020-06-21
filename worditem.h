#ifndef WORDITEM_H
#define WORDITEM_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class WordItem				//一个单词项
{
public:
    string word;			//英文拼写
    string part_of_speech;	//发音
    string meaning;			//汉语解释
    string example;			//例句
    string example_meaning;	//例句解释

    WordItem();
    ~WordItem();
    void display()
    {
        cout << *this;
    }
    string getEnglish(){
        return this->word;
    }
    string getChinese(){
        return this->meaning;
    }
    friend ofstream & operator <<(ofstream & ofs, WordItem & wl);	//支持使用"fout<<wi"写入文件
    friend ifstream & operator >>(ifstream & ifs, WordItem & wl);	//支持使用"fin>>wi"读取文件
    friend ostream & operator <<(ostream & ofs, WordItem & wl);		//支持使用"cout<<wi"显示WordItem
    friend istream & operator >>(istream & ifs, WordItem & wl);		//支持使用"cin>>wi"从键盘输入WordItem
//	WordItem & operator =(WordItem & wi);
//	bool operator ==(WordItem wl);
};

#endif
