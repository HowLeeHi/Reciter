#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>
#include <stdio.h>
#include <QMainWindow>
#include "reciter.h"
#include <QTextCodec>
#include <QButtonGroup>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Reciter reciter;//直接放public省去不必要的麻烦
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_changeList_clicked();

    void on_goStudy_clicked();

    void on_reviewAndTest_clicked();

    void on_GoStudy_back_clicked();

    void on_ReviewAndTest_back_clicked();

    void on_GoStudy_unknow_clicked();

    void on_GoStudy_next_clicked();

    void on_GoStudy_know_clicked();

    void on_Schedule_back_clicked();

    void on_changePlan_clicked();

    void on_test_confirm_button_released();

    void on_test_next_released();

    void on_Button_A_released();

    void on_Button_B_released();

    void on_Button_C_released();

    void on_Button_D_released();

    void on_En_Zh_clicked();

    void on_Zh_En_clicked();
    void search();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_Schudule_OK_clicked();

    void on_Schedule_reset_clicked();

private:
    Ui::MainWindow *ui;
    //----------测验用--------------
    int scores;                                     //分数
    unsigned int index_options[4];                  //选项对应单词表下标
    int ans;                                        //正确选项
    int testnum = this->reciter.log.reviewNum;      //题目数量 (0-99)
    bool exam_flag = true;                          //考试类型 true：英译汉  false：汉译英 (默认为true)
    int n;                                          //考试进度 （0 - testnum）
    unsigned int index_testNum[10];                 //题目对应单词表下标

};

#endif // MAINWINDOW_H
