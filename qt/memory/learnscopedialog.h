#ifndef LEARNSCOPEDIALOG_H
#define LEARNSCOPEDIALOG_H

#include <QDialog>
#include "memorymain.h"

#define DEFOULT_NUM 20
namespace Ui {
class LearnScopeDialog;
}

class MemoryMain;

class LearnScopeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LearnScopeDialog(QWidget *parent = 0);
    ~LearnScopeDialog();

    MemoryMain *parentWin;

    void initUI();
    void initData();

    int getFrom();
    int getTotal();

private slots:
    void on_cancelbtn_clicked();

    void on_obtun_clicked();

private:
    Ui::LearnScopeDialog *ui;
};

#endif // LEARNSCOPEDIALOG_H
