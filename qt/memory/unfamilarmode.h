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
public:
    explicit UnfamilarMode(MemoryMain* m = nullptr);

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
};

#endif // UNFAMILARMODE_H
