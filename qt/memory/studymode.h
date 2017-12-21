#ifndef STUDYMODE_H
#define STUDYMODE_H

#include "modeparent.h"
#include "memorymain.h"
#include "learnscopeentity.h"
#include "showwin.h"
#include "QMessageBox"

class MemoryMain;
class ModeParent;
class LearnScopeEntity;


class StudyMode : public ModeParent
{
public:
    explicit StudyMode(MemoryMain* m = nullptr);

    //变量
    int currID;
    bool isShowPic;
    QString currPath;
    QString currNumText;
    QStack<int> backStack;
    // ui
    ShowWin *leftWidget;
    StateWin *rightWidget;

    //函数
    void showImageAndLabel(QString path, QString text, bool ispic);
    void updateStateUI();
    void updateByID(int id);

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

#endif // STUDYMODE_H
