#ifndef STATEWIN_H
#define STATEWIN_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include "timerlabel.h"
#include <QVBoxLayout>
class StateWin : public QWidget
{
public:
    explicit StateWin(QWidget *parent = nullptr);

    void initUI();
    QVBoxLayout *stateLayout;
    QLabel* processTextLabel;
    QProgressBar *stateProcessBar;
    void updateStateUI(int showID, int numSize);
    void resetTimerWin();

    TimerLabel *timeLabel;

    int getTimerWinSec();
    void stopTimerWin();
    void startTimeWin();
};

#endif // STATEWIN_H
