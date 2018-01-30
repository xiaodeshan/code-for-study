#ifndef TESTPLAYER_H
#define TESTPLAYER_H

#include <QWidget>
#include "generalplayer.h"
#include <QFileDialog>
namespace Ui {
class TestPlayer;
}

class TestPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit TestPlayer(QWidget *parent = 0);
    ~TestPlayer();

    GeneralPlayer player;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void slotDurationChanged(qint64 dur);
    void slotError(QMediaPlayer::Error error);
    void slotPositionChanged(qint64);
    void slotSliderPosChanged(int val);


    void on_pushButton_5_clicked();

    void slotBufferStatusChanged(int percentFilled);


    void on_pushButton_6_clicked();

    void slotStateChanged(QMediaPlayer::State state);
    void slotMediaStatusChanged(QMediaPlayer::MediaStatus);

private:
    Ui::TestPlayer *ui;
};

#endif // TESTPLAYER_H
