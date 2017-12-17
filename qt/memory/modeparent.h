#ifndef MODEPARENT_H
#define MODEPARENT_H

#include <QObject>
//#include "memorymain.h"

class MemoryMain;

class ModeParent
{
public:

    explicit ModeParent(MemoryMain* m = nullptr){
        this->memoryMain = m;
    }

    virtual void handlerNext() = 0;
    virtual void handlerLast() = 0;
    virtual void handlerChoosen() = 0;
    virtual void handlerLeft() = 0;
    virtual void handlerRestart() = 0;
    virtual void getModeName() = 0;

signals:

public slots:

protected:
    MemoryMain *memoryMain;
};

#endif // MODEPARENT_H
