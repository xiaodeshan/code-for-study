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
    if(!isShowPic){
        isShowPic = true;
        showImageAndLabel(currPath, currNumText + " " + memoryMain->cardNames->at(currID), isShowPic);
    }else{
        if(isEnded()){
            rightWidget->stopTimerWin();
            QString msg = "恭喜, 你已经学习完成了当前内容.\n是否重新开始学习?";

            int choose = QMessageBox::information(memoryMain, "Info", msg,
                                                  QMessageBox::Ok, QMessageBox::Cancel);

            if(choose == QMessageBox::Ok){
                rightWidget->startTimeWin();
                handlerRestart();
            }

        }else{
            isShowPic = false;
            backStack.push(currID);
            updateByID(getNextId());
            updateStateUI();
        }
    }
}

void CheckMode::handlerLast()
{
    if(!isShowPic){
        if(!backStack.isEmpty()){
            int last = backStack.pop();
            updateByID(last);
            updateStateUI();
        }else{
            QMessageBox::information(memoryMain, "提示", "已经是第一个了",
                                     QMessageBox::Ok);
        }
    }else{
        isShowPic = false;
        updateByID(currID);
    }
}

void CheckMode::handlerChoosen()
{
    isShowPic = false;

    currID = getNextId();
    updateByID(currID);

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
    if(learnScopeEntity.valid())
        return getRandomByFromTo(learnScopeEntity.fromID, learnScopeEntity.toID);
    else
        return getRandomByFromTo(0, memoryMain->getTrueSize() - 1);
}

int CheckMode::getLastId()
{
    return -1;
}

int CheckMode::getNumSize()
{
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();
    if(learnScopeEntity.valid())
        return learnScopeEntity.learnNum;
    return -1;
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

int CheckMode::getCurrId()
{
    return currID;
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
    int showID = backStack.size() + 1;
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

