#include "settings.h"

Settings::Settings()
{
    this->read();
}

void Settings::read()
{
    ifstream fin(QCoreApplication::applicationDirPath().toStdString()+"/settings/settings.txt");

    if(fin)
    {
        fin >> this->filename_record >> this->filepath_record;
    }
    else    //如果缺少必要的文件系统，就自动创建
    {
        this->filename_record = "null";
        this->filepath_record = QCoreApplication::applicationDirPath().toStdString()+"/settings";
        QDir dir;
        if(!dir.exists(QCoreApplication::applicationDirPath()+"/settings"))
            dir.mkdir(QCoreApplication::applicationDirPath()+"/settings");
        this->write();
    }
}

void Settings::write()
{
    ofstream fout(QCoreApplication::applicationDirPath().toStdString()+"/settings/settings.txt");

    fout << this->filename_record << endl << this->filepath_record;
}
