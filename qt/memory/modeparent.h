#ifndef MODEPARENT_H
#define MODEPARENT_H

#include <QObject>
#include "learnscopeentity.h"

class MemoryMain;
class LearnScopeEntity;


class ModeParent
{
public:

    explicit ModeParent(MemoryMain* m = nullptr);

    //LearnScopeEntity getLearnScopeEntity();

    virtual void handlerNext() = 0;
    virtual void handlerLast() = 0;
    virtual void handlerChoosen() = 0;
    virtual void handlerLeft() = 0;
    virtual void handlerRestart() = 0;
    virtual QString getModeName() = 0;
    virtual int getNextId() = 0;
    virtual int getLastId() = 0;
    virtual int getNumSize() = 0;
    virtual bool isEnded() = 0;

signals:

public slots:

protected:
    MemoryMain *memoryMain;
};

#endif // MODEPARENT_H

