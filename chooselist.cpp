#include "chooselist.h"
#include "ui_chooselist.h"

ChooseList::ChooseList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseList)
{
    ui->setupUi(this);
}

ChooseList::~ChooseList()
{
    delete ui;
}
