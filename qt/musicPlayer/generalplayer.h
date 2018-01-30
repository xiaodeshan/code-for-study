#ifndef GENERALPLAYER_H
#define GENERALPLAYER_H

#include <qmediaplayer.h>

class GeneralPlayer : public QObject
{
    Q_OBJECT

public:
    GeneralPlayer();

    void setMedia(QString path);
    void play();
    void pause();
    void stop();
    int volume();
    void setVolume(int);

    int getDuration();
    QString getQint64String(qint64 durInt);
    void setPosition(qint64 position);

public slots:
    // 这里应该不处理信号，后面将封装player信号到外部接收

// 以后会变为私有
public:
    QMediaPlayer *player;

signals:
    void durationChanged(qint64);
    void error(QMediaPlayer::Error);
    void positionChanged(qint64);
};

#endif // GENERALPLAYER_H
