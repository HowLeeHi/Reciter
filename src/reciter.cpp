#include <string>
#include <fstream>
#include <algorithm>
#include "reciter.h"
#include <ctime>
#include <string.h>
using namespace std;

class myless
{
public:
    //重载运算符，为排序做准备
    bool operator()(WordItem a, WordItem b) {
        //按照字典序排列
        return a.getEnglish() < b.getEnglish();
    }
};


Reciter::Reciter()
{
    QDir dir;
    if(!dir.exists(QCoreApplication::applicationDirPath()+"/wordlist"))
        dir.mkdir(QCoreApplication::applicationDirPath()+"/wordlist");

    ifstream fin;
    ofstream fout(QCoreApplication::applicationDirPath().toStdString()+"/wordlist/null.txt"); //生成程序必须的null.txt
    fout << "";

    this->wordlist_address = this->settings.filepath_record+"/"+this->settings.filename_record+".txt";
    fin.open(this->wordlist_address);
    if(!fin) this->set_address(QCoreApplication::applicationDirPath().toStdString()+"/wordlist/null.txt");

    this->load_wordlist();

    this->change_log();

    this->change_review();

    this->reset = false;
}


Reciter::~Reciter()
{
}

void Reciter::display()
{
    if(this->is_empty()){
        cout << "单词表是空的" << endl;
    }
    unsigned int length = this->wordlist.size();
    for(unsigned int i = 0; i < length; i++){
        cout << this->wordlist[i];
    }
}

int Reciter::get_size()
{
    return this->wordlist.size();
}

void Reciter::create_wordlist()
{
    string name;
    char cmd;
    WordItem wi;
    ofstream fout;

    cout << "给单词表起个名字吧：";		//如果没有输入文件名，则用默认文件名"wordlist.txt"
    getline(cin, name);
    if (name != "")
    {
        fout.open(name + ".txt");
    }
    else
    {
        fout.open("wordlist.txt");
    }
    cout << endl;

    cout << "开始添加单词：" << endl;
    cout << "（输入<回车>继续）" << endl;
    cout << "（输入其他键退出）" << endl;
    cin.get(cmd);
    while (cmd == '\n')
    {
        cin >> wi;
        fout << wi;
        cout << "（输入<回车>继续）" << endl;
        cout << "（输入其他键退出）" << endl;
        cin.get(cmd);
    }
}

void Reciter::clear_wordlist()
{
    vector<WordItem> clear;
    this->wordlist.swap(clear);
}

//将文件里的单词表以WordItem类vector的形式存放在内存中
void Reciter::load_wordlist()
{
    WordItem wi;
    ifstream fin(this->wordlist_address);
    this->wordlist.clear();
    while (fin >> wi){
        this->wordlist.push_back(wi);
    }
}

//将内存中的WordItem类vector写入文件
bool Reciter::save_wordlist()
{
    ofstream fout(this->wordlist_address);
    if (this->wordlist.size() == 0) return false;
    for (unsigned int i = 0; i < this->wordlist.size(); i++)
    {
        fout << this->wordlist[i];
    }
    return true;
}

//按照字典序将单词排序
void Reciter::sort_wordlist()
{
    sort(this->wordlist.begin(), this->wordlist.end(), myless());
}

int Reciter::add_word()     //添加一个新单词
{
    cout << "添加单词：" << endl;
    WordItem newWordItem;
    cin >> newWordItem;
    this->wordlist.push_back(newWordItem);
    this->sort_wordlist();
    return 0;
}

//删除第i个WordNode节点，失败则返回值为负数
int Reciter::delete_word(int i)
{
    if((i<0) || (i>=(int)(this->wordlist.size()))){
        //cout<<"下标不合法！"<<endl;
        return -1;
    }
    this->wordlist.erase((this->wordlist.begin())+i);
    return 1;
}

//根据单词二分查找相应的下标
int Reciter::search_word(string word)
{
    int left=0;
    int right=this->get_size()-1;
    //进行二分查找
    while(left<=right){
        //中间元素
        int middle=(left+right)/2;
        //找到目标
        if(this->wordlist[middle].getEnglish() == word)
            return middle;
            //目标在左半部分
        else if(this->wordlist[middle].getEnglish() > word)
            right=middle-1;
            //目标在右半部分
        else left=middle+1;
    }
    return -1;
}

//选择汉语解释，利用数组返回4个选项，返回值为正确选项
int Reciter::test_answer_CN(unsigned int i, unsigned int array[4])
{
    srand(unsigned(time(0)));
    unsigned int tmp1 = i;
    //随机生成4个错误选项
    for(int j=0;j<4;j++){
        unsigned int tmp2=rand()%(this->get_size());
        bool repeat=false;
        //检查是否有重复的情况
        for(int k=0;k<j;k++){
            if(array[k] == tmp2)
                repeat=true;
        }
        if(repeat || (this->review.reviewlist[tmp1].word == this->wordlist[tmp2].word))
            j--;
        else
            array[j]=tmp2;
    }
    //生成正确选项替代其中一个错误选项
    int ans=rand()%4;
    array[ans]=tmp1;
    return ans;
}

//选择英语解释，利用数组返回4个选项，返回值为正确选项
int Reciter::test_answer_ENG(unsigned int i, unsigned int array[4])
{
    srand(unsigned(time(0)));
    unsigned int tmp1 = i;
    //随机生成4个错误选项
    for(int j=0;j<4;j++){
        unsigned int tmp2=rand()%(this->get_size());
        bool repeat=false;
        //检查是否有重复的情况
        for(int k=0;k<j;k++){
            if(array[k] == tmp2)
                repeat=true;
        }
        if(repeat || (this->review.reviewlist[tmp1].word == this->wordlist[tmp2].word))
            j--;
        else
            array[j]=tmp2;
    }
    //生成正确选项替代其中一个错误选项
    int ans=rand()%4;
    array[ans]=tmp1;
    return ans;
}
//模拟查找单词
void Reciter::search_Word()
{
    char cmd;
    string word;
    cout << "开始查找单词：" << endl;
    cout << "（输入<回车>继续）" << endl;
    cout << "（输入其他键退出）" << endl;
    cin.get(cmd);
    while (cmd == '\n')
    {
        cout << "输入单词拼写：";
        cin >> word;
        int pos = search_word(word);
        if(pos > -1){
            cout << this->wordlist[pos];
        } else {
            cout << "单词表内不存在该单词" << endl;
        }
        cout << "（输入<回车>继续）" << endl;
        cout << "（输入其他键退出）" << endl;
        cin.get(cmd);
        cin.get(cmd);
    }
}

// 汉译英 + 英译汉array存储testnum个题目，单词表为空返回false
bool Reciter::exam(int testNum, unsigned int *array) //array存放单词所对应的编号
{
    if(this->review.reviewlist.size() >0){
        //随机选取testNum个单词
        srand(unsigned(time(0)));
        for(int i = 0; i < testNum; i++){
            unsigned int tmp = rand()%(this->review.reviewlist.size());
            //检查随机生成的单词是否重复
            bool repeat=false;
            for(int j=0;j<i;j++){
                if(array[j] == tmp)
                    repeat=true;
            }
            if(repeat)
                i--;
            else
                array[i]=tmp;
        }
        return true;
    }
    return false;
}

void Reciter::run()
{
    //this->create_wordlist();
    this->load_wordlist();
//	this->display();

//	cout << this->get_size();
//	this->add_word();
//	this->display();

//	this->sort_wordlist();
//	this->display();

//	this->test_answer_CN(0);
//	this->exam();

    this->search_Word();
//	this->set_address("wordlist2.txt");
//	this->save_wordlist();

}

void Reciter::change_log()
{
    this->log.change_wordlistname(this->settings.filename_record);
    this->log.generate_plan(this->wordlist.size());
}

void Reciter::reset_plan()
{
    this->log.reset_plan(this->wordlist.size());
}

void Reciter::change_review()
{
    this->review.wordlistname = this->settings.filename_record;
    this->review.read();
}

bool Reciter::reset_review()
{
    QDir dir(QString::fromStdString(QCoreApplication::applicationDirPath().toStdString()+
                                    "/review/"+
                                    this->settings.filename_record));
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())  {return false;}//文件不存，则返回false
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(fileList.size()>0)
    {
        int infoNum=fileList.size();
        for(int i=infoNum-1;i>=0;i--)
        {
            curFile=fileList[i];
            if(curFile.isFile())//如果是文件，删除文件
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())//如果是文件夹
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size()==0)//下层没有文件或文件夹
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j=0;j<fileList1.size();j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    this->review.read();
    return true;
}
