#include "unfamilarmode.h"

UnfamilarMode::UnfamilarMode(MemoryMain *m): ModeParent(m)
{
    unfamiliarId = -1;
    unfamiliarList = new QList<int>();

    //主界面
    leftWidget = new ShowWin(memoryMain);
    //状态界面
    rightWidget = new StateWin(memoryMain);

    isShowPic = false;
}

void UnfamilarMode::handlerNext()
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

            int x = getNextId();
            updateByID(x);
            updateStateUI();
        }
    }
}

void UnfamilarMode::handlerLast()
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

void UnfamilarMode::handlerChoosen()
{
    currID = 0;
    unfamiliarId = 0;

    updateByID(unfamiliarList->at(0));
    memoryMain->updateLayout(leftWidget, rightWidget);
    updateStateUI();
}

void UnfamilarMode::handlerLeft()
{

}

void UnfamilarMode::handlerRestart()
{

    backStack.clear();
    isShowPic = false;

    currID = 0;
    unfamiliarId = 0;

    updateByID(unfamiliarList->at(0));
    updateStateUI();
}

QString UnfamilarMode::getModeName()
{
    return "陌生模式";
}

int UnfamilarMode::getNextId()
{
    if(unfamiliarId == -1){
        return -1;
    }
    unfamiliarId = unfamiliarId + 1;
    if(unfamiliarId == unfamiliarList->size()){
        unfamiliarId = 0;
    }
    return unfamiliarList->at(unfamiliarId);
}

int UnfamilarMode::getLastId()
{
    return unfamiliarList->at(unfamiliarList->size() - 1);
}

int UnfamilarMode::getNumSize()
{
    return unfamiliarList->size();
}

bool UnfamilarMode::isEnded()
{
    if(backStack.size() + 1 == unfamiliarList->size()){
        return true;
    }
    return false;
}

int UnfamilarMode::getCurrId()
{
    return unfamiliarList->at(currID);
}

void UnfamilarMode::slotAddToUnfamiliar(int id)
{
    for(int i = 0; i < unfamiliarList->size(); i++){
        if(unfamiliarList->at(i) == id){
            return;
        }
    }

    unfamiliarList->append(id);
}

void UnfamilarMode::updateByID(int id)
{
    currPath = memoryMain->getPicPathByid(id);
    currNumText = memoryMain->cardNums->at(id);
    currID = id;

    showImageAndLabel(currPath, currNumText, isShowPic);
}

void UnfamilarMode::showImageAndLabel(QString path, QString text, bool ispic)
{
    leftWidget->showImageAndLabel(path, text, ispic);
}

void UnfamilarMode::updateStateUI()
{
    int showID = backStack.size() + 1;
    rightWidget->updateStateUI(showID, getNumSize());
}


