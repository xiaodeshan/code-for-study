#ifndef LEARNSCOPEENTITY_H
#define LEARNSCOPEENTITY_H

#include "modeparent.h"

class ModeParent;

// 学习范围实体
class LearnScopeEntity
{
public:
    //成员
    int learnNum;
    int fromID;
    int toID;

    //函数
    bool valid();
    LearnScopeEntity(int learnNum = -1, int fromID = -1, int toID = -1);
    static LearnScopeEntity* crateEmptyLearnScopeEntity();
};

#endif // LEARNSCOPEENTITY_H
