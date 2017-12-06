#include "timerlabel.h"

TimerLabel::TimerLabel(QWidget *parent) : QLabel(parent)
{
    sec = 0;
    timer = new QTimer();
    setFont(QFont("Times", 30, QFont::Bold));

    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));
}

void TimerLabel::start()
{
    timer->start(1000);
}

void TimerLabel::stop()
{
    timer->stop();
}

void TimerLabel::reset()
{
    setText("00:00");
    sec = 0;
}

QString TimerLabel::getSecText()
{
    QString result = "";
    if(sec < 60 * 60){
        int min = sec / 60;
        int trueSec = sec - min * 60;

        if(min < 10){
            result += "0" + QString::number(min);
        }else{
            result += QString::number(min);
        }

        result += ":";

        if(trueSec < 10){
            result += "0" + QString::number(trueSec);
        }else{
            result += QString::number(trueSec);
        }

        return result;
    }else if(sec < 60 * 60 * 24){
        int hour = sec / 3600;
        int min = (sec - hour * 60) / 60;
        int trueSec = sec - min * 60;

        if(hour < 10){
            result += "0" + QString::number(hour);
        }else{
            result += QString::number(hour);
        }
        result += ":";
        if(min < 10){
            result += "0" + QString::number(min);
        }else{
            result += QString::number(min);
        }
        result += ":";
        if(trueSec < 10){
            result += "0" + QString::number(trueSec);
        }else{
            result += QString::number(trueSec);
        }

        return result;

    }else{
        int day = sec / 3600 / 24;
        int hour = (sec - day * 3600 * 24)/ 3600;
        int min = (sec - hour * 60) / 60;
        int trueSec = sec - min * 60;

        result += QString::number(hour) + "天";

        if(hour < 10){
            result += "0" + QString::number(hour);
        }else{
            result += QString::number(hour);
        }
        result += ":";
        if(min < 10){
            result += "0" + QString::number(min);
        }else{
            result += QString::number(min);
        }
        result += ":";
        if(trueSec < 10){
            result += "0" + QString::number(trueSec);
        }else{
            result += QString::number(trueSec);
        }

        return result;
    }
}

void TimerLabel::slotTimeOut()
{
    sec++;
    setText(getSecText());
}
