#include "settings.h"

Settings::Settings()
{
    this->read();
}

void Settings::read()
{
    ifstream fin("./settings/settings.txt");

    if(fin)
    {
        fin >> this->filename_record >> this->filepath_record;
    }
    else    //如果缺少必要的文件系统，就自动创建
    {
        this->filename_record = "null";
        this->filepath_record = "./";
        _mkdir("./settings/");
        this->write();
    }
}

void Settings::write()
{
    ofstream fout("./settings/settings.txt");

    fout << this->filename_record << endl << this->filepath_record;
}
