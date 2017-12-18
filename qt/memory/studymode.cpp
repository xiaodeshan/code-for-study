#include "studymode.h"

StudyMode::StudyMode(MemoryMain* m) : ModeParent(m)
{
    currID = 0;

    //主界面
    leftWidget = new ShowWin(memoryMain);
    //状态界面
    rightWidget = new StateWin(memoryMain);
}

void StudyMode::handlerNext()
{
    if(!isShowPic){
        isShowPic = true;
        showImageAndLabel(currPath, currNumText + " " + memoryMain->cardNames->at(currID), isShowPic);
    }else{
        if(isEnded()){
            rightWidget->stopTimerWin();
            QString msg = "Congratulations, You've finished the study.\nDid you want to continue study?";

            int choose = QMessageBox::information(memoryMain, "Info", msg,
                                                  QMessageBox::Ok, QMessageBox::Cancel);

            if(choose == QMessageBox::Ok){
                rightWidget->startTimeWin();
                handleRestart();
            }

        }else{
            isShowPic = false;
            backStack.push(currID);
            updateByID(getNextId());
            updateStateUI();
        }
    }
}

void StudyMode::handlerLast()
{
    if(!isShowPic){
        //back to last
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

void StudyMode::handlerChoosen()
{
    leftWidget->close();
    leftWidget = new ShowWin(memoryMain);
    leftWidget->show();
    rightWidget->show();
    isShowPic = false;

    updateByID(currID);

    memoryMain->updateLayout(leftWidget, rightWidget);
    updateStateUI();
}

void StudyMode::handlerLeft()
{

}

void StudyMode::handlerRestart()
{

}

void StudyMode::getModeName()
{

}

int StudyMode::getNextId()
{
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();

    if(learnScopeEntity.valid())
        return (currID + 1) % getNumSize();
    else{
        int last = getLastId();

        if(currID == last)
            return learnScopeEntity.fromID;
        return currID + 1;
    }

}

int StudyMode::getLastId()
{
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();
    if(learnScopeEntity.fromID == -1)
        return memoryMain->getTrueSize() - 1;

    int last = learnScopeEntity.fromID + learnScopeEntity.learnNum - 1;
    if(last > memoryMain->getTrueSize() - 1)
        last = memoryMain->getTrueSize() - 1;

    return last;
}

int StudyMode::getNumSize()
{
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();

    if(!learnScopeEntity.valid())
        return memoryMain->getTrueSize();

    int sizeT = getLastId() - learnScopeEntity.fromID + 1;
    return learnScopeEntity.learnNum > sizeT ? sizeT : learnScopeEntity.learnNum;
}

bool StudyMode::isEnded()
{
    return currID == getLastId();
}

void StudyMode::handleRestart()
{

}

void StudyMode::showImageAndLabel(QString path, QString text, bool ispic)
{
    leftWidget->showImageAndLabel(path, text, ispic);
}

void StudyMode::updateStateUI()
{
    int showID = currID;
    LearnScopeEntity learnScopeEntity = memoryMain->getLearnScopeEntity();

    if(learnScopeEntity.fromID != -1)
        showID = currID - learnScopeEntity.fromID;
    rightWidget->updateStateUI(showID, getNumSize());
}


void StudyMode::updateByID(int id)
{
    currPath = memoryMain->getPicPathByid(id);
    currNumText = memoryMain->cardNums->at(id);
    currID = id;

    showImageAndLabel(currPath, currNumText, isShowPic);
}



