#ifndef LEARNSCOPEENTITY_H
#define LEARNSCOPEENTITY_H

#include "modeparent.h"

class ModeParent;

// 学习范围实体
class LearnScopeEntity
{
public:
    int learnNum;
    int fromID;
    int toID;

    LearnScopeEntity(int learnNum = -1, int fromID = -1, int toID = -1);
    bool valid();

    static LearnScopeEntity* crateEmptyLearnScopeEntity();
};

#endif // LEARNSCOPEENTITY_H
