#include "learnscopedialog.h"
#include "ui_learnscopedialog.h"

LearnScopeDialog::LearnScopeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LearnScopeDialog)
{
    ui->setupUi(this);

    initUI();

    parentWin = (MemoryMain*)(this->parent());

    initData();
}

LearnScopeDialog::~LearnScopeDialog()
{
    delete ui;
}

void LearnScopeDialog::initUI()
{
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    setFixedSize(size());
    this->setWindowTitle("学习内容设置");
}

void LearnScopeDialog::initData()
{
    if(parentWin->mode == parentWin->studyMode){
        ui->fromEdit->setText(QString::number(parentWin->currID + 1));
    }else{
        ui->fromEdit->setEnabled(false);
    }

    ui->lineEdit->setText(QString::number(DEFOULT_NUM));
}

int LearnScopeDialog::getFrom()
{
    return ui->fromEdit->text().toInt();
}

int LearnScopeDialog::getTotal()
{
    return ui->lineEdit->text().toInt();
}

void LearnScopeDialog::on_cancelbtn_clicked()
{
    close();
}

void LearnScopeDialog::on_obtun_clicked()
{
    accept();
}


