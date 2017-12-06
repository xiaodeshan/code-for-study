#ifndef LEARNSCOPEDIALOG_H
#define LEARNSCOPEDIALOG_H

#include <QDialog>
#include <QMessageBox>
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

    QString getFromText();
    int getStartID();
    int getTotal();
    int getToID();

    int startID;
    int endID;

private slots:
    void on_cancelbtn_clicked();

    void on_obtun_clicked();

    void on_fromEdit_textChanged(const QString &arg1);

    void on_endEdit_textChanged(const QString &arg1);

private:
    Ui::LearnScopeDialog *ui;
};

#endif // LEARNSCOPEDIALOG_H
