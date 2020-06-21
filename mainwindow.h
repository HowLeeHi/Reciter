#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reciter.h"
#include <QTextCodec>

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

private:
    Ui::MainWindow *ui;
    unsigned int index;
};

#endif // MAINWINDOW_H
