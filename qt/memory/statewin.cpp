#include "statewin.h"

StateWin::StateWin(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void StateWin::initUI()
{
    stateLayout = new QVBoxLayout(this);

    QLabel *stateTextLabel = new QLabel("study progress");
    stateTextLabel->setFont(QFont("Times", 30, QFont::Bold));
    processTextLabel = new QLabel("0/0");
    processTextLabel->setFont(QFont("Times", 20, QFont::Bold));
    stateProcessBar = new QProgressBar(this);
    timeLabel = new TimerLabel(this);
    timeLabel->start();

    stateProcessBar->setMaximum(100);
    stateProcessBar->setMinimum(0);
    stateProcessBar->setValue(0);
    stateProcessBar->setTextVisible(false);

    stateLayout->addWidget(stateTextLabel, 0, Qt::AlignTop);
    stateLayout->addWidget(processTextLabel, 0, Qt::AlignTop);
    stateLayout->addWidget(stateProcessBar, 0, Qt::AlignTop);
    stateLayout->addWidget(timeLabel, 0, Qt::AlignTop);
    stateLayout->addStretch();
    stateLayout->setContentsMargins(20, 20, 20, 0);

    this->setLayout(stateLayout);
}

void StateWin::updateStateUI(int showID, int numSize)
{
    QString processText = QString::number(showID + 1) + "/" + QString::number(numSize);

    processTextLabel->setText(processText);
    stateProcessBar->setValue(100 * (showID + 1) / numSize);
}

void StateWin::resetTimerWin()
{
    timeLabel->reset();
}

int StateWin::getTimerWinSec()
{
    return timeLabel->sec;
}

void StateWin::stopTimerWin()
{
    timeLabel->stop();
}

void StateWin::startTimeWin()
{
    timeLabel->start();
}
