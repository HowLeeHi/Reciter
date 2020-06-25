#ifndef LOG_H
#define LOG_H

#include <string>
#include <QDate>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <QCoreApplication>
#include <QDir>
using namespace std;

class Log
{
public:
    string wordlistname;
    unsigned long index_recordOfGoStudy;
    QDate startDate;
    QDate deadline;
    qint64 daysNum;
    QDate lastPlan;
    unsigned int newWordNum;
    unsigned int reviewNum;

    Log(string wordlistname = "null");
    ~Log();
    void read();
    void write();
    void change_wordlistname(string newwordlistname);
    void generate_plan(unsigned wordlistSize);
    void change_plan(unsigned wordlistSize);
    void reset_plan(unsigned int wordlistSize);
};

#endif // LOG_H
