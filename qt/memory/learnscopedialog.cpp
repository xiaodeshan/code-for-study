#include "learnscopedialog.h"
#include "ui_learnscopedialog.h"

LearnScopeDialog::LearnScopeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LearnScopeDialog)
{
    ui->setupUi(this);
    parentWin = (MemoryMain*)(this->parent());

    initUI();
    initDataByMode(parentWin->mode);
}

LearnScopeDialog::~LearnScopeDialog()
{
    delete ui;
}

void LearnScopeDialog::initUI()
{
    // remove hint button
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    setFixedSize(size());
    this->setWindowTitle("Study Scope Setting");

    initUIByMode(parentWin->mode);
}

void LearnScopeDialog::initDataByMode(StudyMode mode)
{
    switch (mode) {
    case studyMode:
        ui->fromEdit->setText(parentWin->currNumText);
        break;
    case checkMode:
        ui->fromEdit->setText("00");
        break;
    case trainMode:
        break;
    case unfamiliarMode:
        assert(0);
        break;
    default:
        assert(0);
    }

    ui->countEdit->setText(QString::number(DEFOULT_LEARN_NUM));
    ui->totalEdit->setText(QString::number(parentWin->getTrueSize()));
}

void LearnScopeDialog::initUIByMode(StudyMode mode)
{
    switch (mode) {
    case studyMode:
        ui->countEdit->setEnabled(false);
        ui->fromEdit->setFocus();
        ui->fromEdit->selectedText();
        break;
    case checkMode:
        //choose scope to check
        ui->countEdit->setEnabled(true);
        ui->endEdit->setFocus();
        break;
    case trainMode:
        ui->countEdit->setEnabled(true);
        ui->fromEdit->setEnabled(false);
        ui->endEdit->setEnabled(false);
        ui->countEdit->setFocus();
        ui->countEdit->selectedText();
        break;
    case unfamiliarMode:
        assert(0);
        break;
    default:
        assert(0);
    }
    ui->numberEdit->setEnabled(false);
    ui->totalEdit->setEnabled(false);
}

void LearnScopeDialog::on_obtun_clicked()
{
    StudyMode prentMode = parentWin->mode;

    switch (prentMode) {
    case studyMode:
        //TODO
        break;
    case checkMode:
        //TODO
        break;
    case trainMode:{
        QString totalStr = ui->countEdit->text();
        if(totalStr == "" || totalStr.toInt() == 0){
            QMessageBox::information(this, "info", "please input valid value",
                                     QMessageBox::Ok);
            return;
        }

        break;
    }
    case unfamiliarMode:
        assert(0);
        break;
    default:
        assert(0);
    }

    accept();

}

void LearnScopeDialog::on_fromEdit_textChanged(const QString &data)
{
    int pos = parentWin->getNumByText(data);
    startID = pos;
    if(pos != -1){
        if(parentWin->mode == studyMode){
            if(startID > endID){
                ui->countEdit->setText("");
            }else{
                ui->countEdit->setText(QString::number(endID - startID + 1));
            }
        }
        ui->numberEdit->setText(QString::number(pos));
    }else{
        if(parentWin->mode == studyMode){
            ui->numberEdit->setText("");
        }
    }
}

void LearnScopeDialog::on_endEdit_textChanged(const QString &data)
{
    int pos = parentWin->getNumByText(data);
    endID = pos;
    if(pos != -1){
        if(parentWin->mode == studyMode){
            if(startID > endID){
                ui->countEdit->setText("");
            }else{
                ui->countEdit->setText(QString::number(endID - startID + 1));
            }
        }
    }else{
        if(parentWin->mode == studyMode){
            ui->countEdit->setText("");
        }
    }
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
    return ui->countEdit->text().toInt();
}

int LearnScopeDialog::getToID()
{
    return endID;
}

void LearnScopeDialog::on_cancelbtn_clicked()
{
    close();
}
