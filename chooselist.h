#ifndef CHOOSELIST_H
#define CHOOSELIST_H

#include <QDialog>

namespace Ui {
class ChooseList;
}

class ChooseList : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseList(QWidget *parent = nullptr);
    ~ChooseList();

private:
    Ui::ChooseList *ui;
};

#endif // CHOOSELIST_H
