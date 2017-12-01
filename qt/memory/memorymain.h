#ifndef MEMORYMAIN_H
#define MEMORYMAIN_H

#include <QWidget>
#include <qdir.h>
#include <QStringList>
#include <QFileInfoList>
#include <iostream>
#include <random>
#include <time.h>
#include "mainwindow.h"
#include <QImage>
#include <QDebug>
#include <QKeyEvent>
namespace Ui {
class MemoryMain;
}

class MemoryMain : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryMain(QWidget *parent = 0);
    ~MemoryMain();

    QStringList* getAllCardNum(QString path);
    int getRandCardNum(int size);
    void initRand();

    QString getPathByid(int id);
    void showImageAndLabel(QString path, QString text);
    void init();
    int getNumSize();

    QStringList* cardNums;

    bool isShowNum;
    void keyPressEvent(QKeyEvent *event);

    void randShow();

    QString currPath;
    QString currNumText;

private:
    Ui::MemoryMain *ui;
};

#endif // MEMORYMAIN_H
