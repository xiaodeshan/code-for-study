#ifndef CHECKMODE_H
#define CHECKMODE_H

#include "modeparent.h"
#include "memorymain.h"
#include "learnscopeentity.h"

class MemoryMain;
class ModeParent;
class LearnScopeEntity;


class CheckMode : public ModeParent
{
public:
    explicit CheckMode(MemoryMain* m = nullptr);

    //变量
    QStack<int> backStack;
    bool isShowPic;
    int currID;
    QString currPath;
    QString currNumText;
    // ui
    ShowWin *leftWidget;
    StateWin *rightWidget;

    // 函数
    int getRandomByFromTo(int from, int to);
    void updateByID(int id);
    void updateStateUI();
    void showImageAndLabel(QString path, QString text, bool ispic);
    void initSrand();

    //虚函数
    void handlerNext();
    void handlerLast();
    void handlerChoosen();
    void handlerLeft();
    void handlerRestart();
    QString getModeName();
    int getNextId();
    int getLastId();
    int getNumSize();
    bool isEnded();
    int getCurrId();
};

#endif // CHECKMODE_H
