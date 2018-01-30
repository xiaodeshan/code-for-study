#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sec = 0;

    timer.start(1000);

    connect(&timer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));

    this->setWindowFlags((this->windowFlags() | Qt::WindowStaysOnTopHint) & ~Qt::WindowMinMaxButtonsHint);
    this->setWindowTitle("秒表");
    setFixedSize(QSize(150, 58));

    this->hide();
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getSecText()
{
    QString result = "";
    if(sec < 60 * 60){
        int min = sec / 60;
        int trueSec = sec - min * 60;

        if(min < 10){
            result += "0" + QString::number(min);
        }else{
            result += QString::number(min);
        }

        result += ":";

        if(trueSec < 10){
            result += "0" + QString::number(trueSec);
        }else{
            result += QString::number(trueSec);
        }

        return result;
    }else if(sec < 60 * 60 * 24){
        int hour = sec / 3600;
        int min = (sec - hour * 3600) / 60;
        int trueSec = sec - hour * 3600 - min * 60;

        if(hour < 10){
            result += "0" + QString::number(hour);
        }else{
            result += QString::number(hour);
        }
        result += ":";
        if(min < 10){
            result += "0" + QString::number(min);
        }else{
            result += QString::number(min);
        }
        result += ":";
        if(trueSec < 10){
            result += "0" + QString::number(trueSec);
        }else{
            result += QString::number(trueSec);
        }

        return result;

    }else{
        int day = sec / 3600 / 24;
        int hour = (sec - day * 3600 * 24)/ 3600;
        int min = (sec - hour * 60) / 60;
        int trueSec = sec - min * 60;

        result += QString::number(hour) + "天";

        if(hour < 10){
            result += "0" + QString::number(hour);
        }else{
            result += QString::number(hour);
        }
        result += ":";
        if(min < 10){
            result += "0" + QString::number(min);
        }else{
            result += QString::number(min);
        }
        result += ":";
        if(trueSec < 10){
            result += "0" + QString::number(trueSec);
        }else{
            result += QString::number(trueSec);
        }

        return result;
    }
}

void MainWindow::slotTimeOut()
{
    sec++;
    ui->label->setText(getSecText());
}
