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
#include "trainwin.h"
#include "timerlabel.h"
#include "statewin.h"
#include "showwin.h"
#include <QContextMenuEvent>
#include <QApplication>
#include <QClipboard>
#include "learnscopedialog.h"
#include "global.h"

#define CARD_PATH "./image/"
#define CARD_NAME_PATH "./raw/names.txt"

class LearnScopeDialog;


class MemoryMain : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryMain(QWidget *parent = 0);
    ~MemoryMain();

    // 变量

    // 根据文件名来提取的id,可能存在"01"等id
    QStringList* cardNums;
    QStringList* cardNames;
    QList<int>*  unfamiliarList;
    int unfamiliarId;

    bool isShowPic;
    QString currPath;
    QString currNumText;
    int currID;
    QStack<int> backStack;
    QMenuBar *menuBar;
    StudyMode mode;
    // 是否首次运行
    bool justStart;

    //学习范围
    int learnNum;
    int fromID;
    int toID;

    // ui
    QHBoxLayout *widgetLayout;
    QWidget *rightWidget;
    QWidget *leftWidget;
    LearnScopeDialog* dialog;

    int getRandCardNum(int size);
    QString getPicPathByid(int id);
    int getNextID();
    int getNumSize();
    void updateByID(int id);
    void init();
    void initSrand();
    void initMenuBar();
    void initBackground();
    void initUI();
    void initScope();
    void readAllCardInfoFromFile(QString path);
    void showImageAndLabel(QString path, QString text, bool ispic);
    void startProg();
    void updateStateUI();
    int getTrueSize();
    int getLast();
    void updateLayout();
    StateWin* getStateWin();
    ShowWin* getShowWin();
    TrainWin *getTrainWin();
    int getNumByText(QString data);
    void resetLearn();
    int getRandomByFromTo(int from, int to);
    void copyText(QString);
    bool isEnded();
    void handleKeyNext();
    void handleKeyLast();


    void keyPressEvent(QKeyEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

public slots:
    void slotChooseStydyMode(bool triggle);
    void slotChooseCheckMode(bool triggle);
    void slotChooseTrainMode(bool triggle);
    void slotunfamiliarMode(bool triggle);
    void slotChooseScope();
    void slotAddToUnfamiliar(int id);
    void slotCopyText();
    void slotAddToUnfamiliarAction();

signals:
    void signalAddToUnfamiliar(int id);


};

#endif // MEMORYMAIN_H
