#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reciter.h"
#include <QTextCodec>
#include <QButtonGroup>
#include <QDate>
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

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_Schudule_OK_clicked();

    void on_Schedule_reset_clicked();

private:
    Ui::MainWindow *ui;
    unsigned int index;     //下一个需学习的单词下标
    //----------测验用--------------
    int scores;
    unsigned int index_options[4];
    int ans;
    int testnum = 10;
    int n;
    unsigned int index_testNum[10];

};

#endif // MAINWINDOW_H
