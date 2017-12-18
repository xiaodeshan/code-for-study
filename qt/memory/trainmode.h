#ifndef TRAINMODE_H
#define TRAINMODE_H

#include "modeparent.h"
#include "memorymain.h"
#include "learnscopeentity.h"

class MemoryMain;
class ModeParent;
class LearnScopeEntity;

class TrainMode : public ModeParent
{
public:
    explicit TrainMode(MemoryMain* m = nullptr);

    void handlerNext();
    void handlerLast();
    void handlerChoosen();
    void handlerLeft();
    void handlerRestart();
    void getModeName();
    int getNextId();
    int getLastId();
    int getNumSize();
    bool isEnded();
};

#endif // TRAINMODE_H
