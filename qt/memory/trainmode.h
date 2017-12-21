#ifndef TRAINMODE_H
#define TRAINMODE_H

#include "modeparent.h"
#include "memorymain.h"
#include "learnscopeentity.h"
#include "trainwin.h"

class MemoryMain;
class ModeParent;
class LearnScopeEntity;

class TrainMode : public ModeParent
{
public:
    explicit TrainMode(MemoryMain* m = nullptr);

    //变量
    TrainWin *trainWin;
    StateWin *stateWin;

    //函数
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

};

#endif // TRAINMODE_H
