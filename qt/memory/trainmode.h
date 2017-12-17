#ifndef TRAINMODE_H
#define TRAINMODE_H

#include "modeparent.h"
#include "memorymain.h"

class MemoryMain;
class ModeParent;

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
};

#endif // TRAINMODE_H
