#include <iostream>
#include <fstream>
#include <string>
#include "worditem.h"
using namespace std;


WordItem::WordItem()
{
}


WordItem::~WordItem()
{
}

ofstream & operator <<(ofstream & ofs, WordItem & wl)
{
    ofs << wl.word << endl << wl.part_of_speech << endl << wl.meaning << endl << wl.example << endl << wl.example_meaning << endl << endl;
    return ofs;
}

ifstream & operator >>(ifstream & ifs, WordItem & wl)
{
    getline(ifs, wl.word);
    getline(ifs, wl.part_of_speech);
    getline(ifs, wl.meaning);
    getline(ifs, wl.example);
    getline(ifs, wl.example_meaning);
    ifs.get();
    return ifs;
}

ostream & operator <<(ostream & os, WordItem & wl)
{
    if (wl.word == "")
    {
        os << "<暂无拼写>";
    }
    else
    {
        os << wl.word;
    }
    os << endl;

    if (wl.part_of_speech == "")
    {
        os << "<暂无词性>";
    }
    else
    {
        os << wl.part_of_speech;
    }
    os << endl;

    if (wl.meaning == "")
    {
        os << "<暂无中文释义>";
    }
    else
    {
        os << wl.meaning;
    }
    os << endl;

    if (wl.example == "")
    {
        os << "<暂无例句>";
    }
    else
    {
        os << wl.example;
    }
    os << endl;

    if (wl.example_meaning == "")
    {
        os << "<暂无例句翻译>";
    }
    else
    {
        os << wl.example_meaning;
    }
    os << endl << endl;

    return os;
}

istream & operator >>(istream & is, WordItem & wl)
{
    cout << "单词拼写：";
    getline(is, wl.word);
    cout << "单词词性：";
    getline(is, wl.part_of_speech);
    cout << "中文释义：";
    getline(is, wl.meaning);
    cout << "例句：";
    getline(is, wl.example);
    cout << "例句翻译：";
    getline(is, wl.example_meaning);
    return is;
}
