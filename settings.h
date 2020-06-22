#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <fstream>
using namespace std;

class Settings
{
public:
    string filename_record;     //记录上一次设置的单词表名称
    string filepath_record;

    Settings();
    void read();
    void write();
};

#endif // SETTINGS_H
