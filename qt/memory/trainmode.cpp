#include "trainmode.h"

TrainMode::TrainMode(MemoryMain *m): ModeParent(m)
{
    trainWin = new TrainWin(memoryMain);
    stateWin = new StateWin(memoryMain);
}

void TrainMode::handlerNext()
{  
    trainWin->nextShow();
    updateStateUI();
}

void TrainMode::handlerLast()
{
    bool succ  = trainWin->lastShow();
    updateStateUI();

    if(!succ){
        QMessageBox::information(memoryMain, "提示", "已经是第一个了",
                                 QMessageBox::Ok);
    }
}

void TrainMode::handlerChoosen()
{
    memoryMain->updateLayout(trainWin, stateWin);
    updateStateUI();
}

void TrainMode::handlerLeft()
{
}

void TrainMode::handlerRestart()
{
    return;
}

QString TrainMode::getModeName()
{
    return "训练模式";
}

int TrainMode::getNextId()
{
    return -1;
}

int TrainMode::getLastId()
{
    return -1;
}

int TrainMode::getNumSize()
{
    return -1;
}

bool TrainMode::isEnded()
{
    return false;
}

int TrainMode::getCurrId()
{
    return -1;
}

void TrainMode::updateStateUI()
{
    int showID = trainWin->backStack.size() + 1;
    stateWin->updateStateUI(showID, getNumSize());
}
