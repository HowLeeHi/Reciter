#include "settings.h"

Settings::Settings()
{
    this->read();
}

void Settings::read()
{
    ifstream fin("./settings/settings.txt");

    fin >> this->filename_record >> this->filepath_record;
}

void Settings::write()
{
    ofstream fout("./settings/settings.txt");

    fout << this->filename_record << endl << this->filepath_record;
}
