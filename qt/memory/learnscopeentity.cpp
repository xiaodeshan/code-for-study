#include "learnscopeentity.h"

LearnScopeEntity::LearnScopeEntity(int learnNum, int fromID, int toID) : learnNum(learnNum), fromID(fromID), toID(toID)
{
}

bool LearnScopeEntity::valid()
{
    if(learnNum == -1 || fromID == -1 || toID == -1)
        return false;
    return true;
}

LearnScopeEntity *LearnScopeEntity::crateEmptyLearnScopeEntity()
{
    return new LearnScopeEntity();
}
