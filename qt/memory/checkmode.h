#ifndef CHECKMODE_H
#define CHECKMODE_H

#include "modeparent.h"
#include "memorymain.h"

class MemoryMain;
class ModeParent;


class CheckMode : public ModeParent
{
public:
    explicit CheckMode(MemoryMain* m = nullptr);

    void handlerNext();
    void handlerLast();
    void handlerChoosen();
    void handlerLeft();
    void handlerRestart();
    void getModeName();
};

#endif // CHECKMODE_H
