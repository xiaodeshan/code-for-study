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
#include "modeparent.h"
#include "studymode.h"
#include "checkmode.h"
#include "trainmode.h"
#include "unfamilarmode.h"

#define CARD_PATH "./image/"
#define CARD_NAME_PATH "./raw/names.txt"

class LearnScopeDialog;
class LearnScopeEntity;

class ModeParent;
class StudyMode;
class CheckMode;
class TrainMode;
class UnfamilarMode;

class MemoryMain : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryMain(QWidget *parent = 0);
    ~MemoryMain();

    // 变量
    // num 为 "01.png" 中的 "01"
    QStringList* cardNums;
    QStringList* cardNames;
    QMenuBar *menuBar;
    //study scope
    LearnScopeEntity *learnScopeEntity;
    // ui
    QHBoxLayout *widgetLayout;
    LearnScopeDialog* dialog;
    // mode
    ModeParent *currModeContext;
    QList<ModeParent*> modeList;

    //函数
    QString getPicPathByid(int id);
    void init();
    void initMenuBar();
    void initBackground();
    void initUI();
    void initScope();
    void initMode();
    void initModeList();
    void bindModeToMenu(QMenu* modeMenu);
    void readAllCardInfoFromFile(QString path);
    int getTrueSize();
    void updateLayout(QWidget *mainPageWidget, QWidget *rightStatusWidget);
    void copyText(QString);
    LearnScopeEntity getLearnScopeEntity();

    //虚函数
    void keyPressEvent(QKeyEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

public slots:
    void slotCopyText();
    void slotAddToUnfamiliarAction();
    void slotModeClick();

signals:
    void signalAddToUnfamiliar(int id);


};

#endif // MEMORYMAIN_H
