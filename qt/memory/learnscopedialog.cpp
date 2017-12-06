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

    ui->lineEdit->setEnabled(false);
    ui->numberEdit->setEnabled(false);
    ui->totalEdit->setEnabled(false);

    ui->fromEdit->setFocus();
    ui->fromEdit->selectedText();
}

void LearnScopeDialog::initData()
{
    if(parentWin->mode == parentWin->studyMode){
        ui->fromEdit->setText(parentWin->currNumText);
    }else{
        ui->fromEdit->setEnabled(false);
    }

    ui->lineEdit->setText(QString::number(DEFOULT_NUM));
    ui->totalEdit->setText(QString::number(parentWin->getTrueSize()));
}

QString LearnScopeDialog::getFromText()
{
    return ui->fromEdit->text();
}

int LearnScopeDialog::getStartID()
{
    return ui->numberEdit->text().toInt();
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
    if(ui->numberEdit->text() == "" || ui->lineEdit->text() == ""){
        QMessageBox::information(this, "info", "please input valid value",
                                 QMessageBox::Ok);
        return;
    }
    accept();
}



void LearnScopeDialog::on_fromEdit_textChanged(const QString &data)
{
    int pos = parentWin->getNumByText(data);
    startID = pos;
    if(pos != -1){
        if(startID > endID){
            ui->lineEdit->setText("");
        }else{
            ui->lineEdit->setText(QString::number(endID - startID + 1));
        }
        ui->numberEdit->setText(QString::number(pos));
    }else{
        ui->numberEdit->setText("");
    }


}

void LearnScopeDialog::on_endEdit_textChanged(const QString &data)
{
    int pos = parentWin->getNumByText(data);
    endID = pos;
    if(pos != -1){
        if(startID > endID){
            ui->lineEdit->setText("");
        }else{
            ui->lineEdit->setText(QString::number(endID - startID + 1));
        }
    }else{
        ui->lineEdit->setText("");
    }


}
