#ifndef UNFAMILARMODE_H
#define UNFAMILARMODE_H

#include "modeparent.h"
#include "memorymain.h"
#include "learnscopeentity.h"

class MemoryMain;
class ModeParent;
class LearnScopeEntity;

class UnfamilarMode : public ModeParent
{
    Q_OBJECT

public:
    explicit UnfamilarMode(MemoryMain* m = nullptr);

    //变量
    int unfamiliarId;
    QList<int>*  unfamiliarList;
    QStack<int> backStack;
    QString currPath;
    QString currNumText;
    int currID;
    bool isShowPic;
    // ui
    ShowWin *leftWidget;
    StateWin *rightWidget;

    //函数
    void updateByID(int id);
    void showImageAndLabel(QString path, QString text, bool ispic);
    void updateStateUI();

    //虚函数
    void handlerNext();
    void handlerLast();
    void handlerChoosen();
    void handlerLeft();
    void handlerRestart();
    QString getModeName();
    int getNextId();
    int getLastId();
    int getNumSize();
    bool isEnded();
    int getCurrId();

public slots:
    void slotAddToUnfamiliar(int id);
};

#endif // UNFAMILARMODE_H
