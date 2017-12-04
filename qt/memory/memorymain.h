#ifndef MEMORYMAIN_H
#define MEMORYMAIN_H

#include <QWidget>
#include <qdir.h>
#include <QStringList>
#include <QFileInfoList>
#include <iostream>
#include <random>
#include <time.h>
#include <QImage>
#include <QDebug>
#include <QKeyEvent>
#include <QStack>
#include <QMessageBox>
#include <QMenuBar>
#include <qlabel.h>
#include <QHBoxLayout>
#include <QProgressBar>
#include "learnscopedialog.h"

#define CARD_PATH "./image/"
#define CARD_NAME_PATH ":/raw/raw/names.txt"

class LearnScopeDialog;

class MemoryMain : public QWidget
{
    Q_OBJECT

public:
    enum Mode{
        studyMode,
        checkMode
    };

public:
    explicit MemoryMain(QWidget *parent = 0);
    ~MemoryMain();

    // 变量

    // 根据文件名来提取的id,可能存在"01"等id
    QStringList* cardNums;
    QStringList* cardNames;
    bool isShowNum;
    QString currPath;
    QString currNumText;
    int currID;
    QStack<int> backStack;
    QMenuBar *menuBar;
    Mode mode;
    // 是否首次运行
    bool justStart;

    //学习范围
    int learnNum;
    int fromID;

    // ui
    QLabel* imageLabel;
    QLabel* numLabel;

    QLabel* processTextLabel;
    QProgressBar *stateProcessBar;
    QVBoxLayout *stateLayout;
    QHBoxLayout *widgetLayout;
    QWidget *rightWidget;
    LearnScopeDialog* dialog;

    int getRandCardNum(int size);
    QString getPathByid(int id);
    int getNextID();
    int getNumSize();
    void updateByID(int id);
    void init();
    void initSrand();
    void initMenuBar();
    void initBackground();
    void initUI();
    void readAllCardInfoFromFile(QString path);
    void showImageAndLabel(QString path, QString text);
    void startProg();
    void updateStateUI();
    int getTrueSize();
    int getLast();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void slotChooseStydyMode(bool triggle);
    void slotChooseCheckMode(bool triggle);
    void slotChooseScope();

};

#endif // MEMORYMAIN_H
