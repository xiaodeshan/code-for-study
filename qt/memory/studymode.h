#ifndef STUDYMODE_H
#define STUDYMODE_H

#include "modeparent.h"
#include "memorymain.h"

class MemoryMain;
class ModeParent;


class StudyMode : public ModeParent
{
public:
    explicit StudyMode(MemoryMain* m = nullptr);

    void handlerNext();
    void handlerLast();
    void handlerChoosen();
    void handlerLeft();
    void handlerRestart();
    void getModeName();
};

#endif // STUDYMODE_H
