#include "trainmode.h"

TrainMode::TrainMode(MemoryMain *m): ModeParent(m)
{

}

void TrainMode::handlerNext()
{

}

void TrainMode::handlerLast()
{

}

void TrainMode::handlerChoosen()
{
    qDebug() << "hahaha";
}

void TrainMode::handlerLeft()
{

}

void TrainMode::handlerRestart()
{

}

QString TrainMode::getModeName()
{
    return "训练模式";
}

int TrainMode::getNextId()
{

}

int TrainMode::getLastId()
{

}

int TrainMode::getNumSize()
{

}

bool TrainMode::isEnded()
{

}
