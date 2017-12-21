#ifndef LEARNSCOPEDIALOG_H
#define LEARNSCOPEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "memorymain.h"
#include "global.h"
#include <assert.h>

#define DEFOULT_LEARN_NUM 20
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

    //变量
    // 父窗口
    MemoryMain *parentWin;
    int startID;
    int endID;

    //函数
    void initUI();
    void initDataByMode();
    void initUIByMode();
    QString getFromText();
    // from to total
    int getStartID();
    int getToID();
    int getTotal();

private slots:
    void on_cancelbtn_clicked();
    void on_obtun_clicked();
    void on_fromEdit_textChanged(const QString &);
    void on_endEdit_textChanged(const QString &);

private:
    Ui::LearnScopeDialog *ui;
};

#endif // LEARNSCOPEDIALOG_H
