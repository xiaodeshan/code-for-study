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
    QStringList *getAllCardName(QString path);

    int getRandCardNum(int size);
    void initRand();

    QString getPathByid(int id);
    void showImageAndLabel(QString path, QString text);
    void init();
    int getNumSize();

    // 根据文件名来提取的id,可能存在"01"等id
    QStringList* cardNums;
    QStringList* cardNames;

    bool isShowNum;
    void keyPressEvent(QKeyEvent *event);

    void randShow();

    QString currPath;
    QString currNumText;
    int currID;

private:
    Ui::MemoryMain *ui;
};

#endif // MEMORYMAIN_H
