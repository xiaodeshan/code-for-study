#include "generalplayer.h"

GeneralPlayer::GeneralPlayer()
{
    player = new QMediaPlayer();

    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SIGNAL(error(QMediaPlayer::Error)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SIGNAL(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SIGNAL(positionChanged(qint64)));
}

void GeneralPlayer::setMedia(QString path)
{
    player->setMedia(QUrl::fromLocalFile(path));
}

void GeneralPlayer::play()
{
    player->play();
}

void GeneralPlayer::pause()
{
    player->pause();
}

void GeneralPlayer::stop()
{
    player->stop();
}

int GeneralPlayer::volume()
{
    return player->volume();
}

void GeneralPlayer::setVolume(int vol)
{
    player->setVolume(vol);
}

int GeneralPlayer::getDuration()
{
    int duration = (int)(player->duration() / 1000.0);
    return duration;
}

QString GeneralPlayer::getQint64String(qint64 durInt)
{
    int sec = (int)(durInt / 1000.0);

    QString result = "";
    // 小于1小时
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
        int min = (sec - hour * 3600) / 60;
        int trueSec = sec - hour * 3600 - min * 60;

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
        int hour = (sec - day * 3600 * 24) / 3600;
        int min = (sec - day * 3600 * 24 - hour * 3600) / 60;
        int trueSec = sec - day * 3600 * 24 - hour * 3600 - min * 60;

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

void GeneralPlayer::setPosition(qint64 position)
{
    //qDebug() << "设置";

    player->setPosition(position);
}


