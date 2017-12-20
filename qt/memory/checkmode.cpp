#include "checkmode.h"

CheckMode::CheckMode(MemoryMain *m): ModeParent(m)
{
    currID = getNextId();

    //主界面
    leftWidget = new ShowWin(memoryMain);
    //状态界面
    rightWidget = new StateWin(memoryMain);
}

void CheckMode::handlerNext()
{

}

void CheckMode::handlerLast()
{

}

void CheckMode::handlerChoosen()
{
    //leftWidget->close();
    //leftWidget = new ShowWin(memoryMain);
    //leftWidget->show();
    //rightWidget->show();
    isShowPic = false;

    currID = getNextId();

    memoryMain->updateLayout(leftWidget, rightWidget);
    updateStateUI();
}

void CheckMode::handlerLeft()
{

}

void CheckMode::handlerRestart()
{  
    backStack.clear();
    isShowPic = false;

    currID = getNextId();

    updateByID(currID);
    updateStateUI();
}

QString CheckMode::getModeName()
{
    return "检查模式";
}

int CheckMode::getNextId()
{
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();
    if(learnScopeEntity.fromID != -1)
        return getRandomByFromTo(learnScopeEntity.fromID, learnScopeEntity.toID);
    else
        return getRandomByFromTo(0, getNumSize() - 1);
}

int CheckMode::getLastId()
{
    return -1;
}

int CheckMode::getNumSize()
{
    return memoryMain->getTrueSize();
}

bool CheckMode::isEnded()
{
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();

    if(learnScopeEntity.valid()){
        if(backStack.size() >= learnScopeEntity.learnNum - 1)
            return true;
    }

    return false;
}

int CheckMode::getRandomByFromTo(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

void CheckMode::updateByID(int id)
{
    currPath = memoryMain->getPicPathByid(id);
    currNumText = memoryMain->cardNums->at(id);
    currID = id;

    showImageAndLabel(currPath, currNumText, isShowPic);
}

void CheckMode::updateStateUI()
{
    int showID = currID;
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();

    if(learnScopeEntity.fromID != -1)
        showID = currID - learnScopeEntity.fromID;
    rightWidget->updateStateUI(showID, getNumSize());
}

void CheckMode::showImageAndLabel(QString path, QString text, bool ispic)
{
    leftWidget->showImageAndLabel(path, text, ispic);
}

void CheckMode::initSrand()
{
    srand(time(0));
}

