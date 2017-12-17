#ifndef UNFAMILARMODE_H
#define UNFAMILARMODE_H

#include "modeparent.h"
#include "memorymain.h"

class MemoryMain;
class ModeParent;

class UnfamilarMode : public ModeParent
{
public:
    explicit UnfamilarMode(MemoryMain* m = nullptr);

    void handlerNext();
    void handlerLast();
    void handlerChoosen();
    void handlerLeft();
    void handlerRestart();
    void getModeName();
};

#endif // UNFAMILARMODE_H
