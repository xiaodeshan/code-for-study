#include "testplayer.h"
#include "ui_testplayer.h"

TestPlayer::TestPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPlayer)
{
    ui->setupUi(this);

    connect(&player, SIGNAL(durationChanged(qint64)), this, SLOT(slotDurationChanged(qint64)));
    connect(&player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(slotError(QMediaPlayer::Error)));
    connect(&player, SIGNAL(positionChanged(qint64)), this, SLOT(slotPositionChanged(qint64)));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(slotSliderPosChanged(int)));

    connect(player.player, SIGNAL(bufferStatusChanged(int)), this, SLOT(slotBufferStatusChanged(int)));
    connect(player.player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(slotStateChanged(QMediaPlayer::State)));
    connect(player.player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(slotMediaStatusChanged(QMediaPlayer::MediaStatus)));
}

TestPlayer::~TestPlayer()
{
    delete ui;
}

void TestPlayer::on_pushButton_clicked()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
                                            tr("选择图像"),
                                            "",
                                            tr("Images (*.mp3 *.aac *.MP3 *.AAC)")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        player.setMedia(filename);
        player.play();
    }
}

void TestPlayer::on_pushButton_3_clicked()
{
    player.pause();
}

void TestPlayer::on_pushButton_2_clicked()
{
    player.play();
}

void TestPlayer::on_pushButton_4_clicked()
{
    player.stop();
}

void TestPlayer::slotDurationChanged(qint64 dur)
{
    ui->horizontalSlider->setMaximum(dur);

    ui->label_duration->setText(player.getQint64String(dur));
}

void TestPlayer::slotError(QMediaPlayer::Error error)
{
    switch (error) {
    case QMediaPlayer::NoError:
        qDebug() << "NoError";
        break;
    case QMediaPlayer::ResourceError:
        qDebug() << "<ResourceError>";
        break;
    case QMediaPlayer::FormatError:
        qDebug() << "FormatError";
        break;
    case QMediaPlayer::NetworkError:
        qDebug() << "NetworkError";
        break;
    case QMediaPlayer::AccessDeniedError:
        qDebug() << "AccessDeniedError";
        break;
    case QMediaPlayer::ServiceMissingError:
        qDebug() << "ServiceMissingError";
        break;
    case QMediaPlayer::MediaIsPlaylist:
        qDebug() << "MediaIsPlaylist";
        break;
    default:
        qDebug() << "others";
        break;
    }
}

void TestPlayer::slotPositionChanged(qint64 curr)
{
    ui->horizontalSlider->setValue(curr);
    ui->label_curr->setText(player.getQint64String(curr));
}

void TestPlayer::slotSliderPosChanged(int val)
{
    player.setPosition(val);
}

void TestPlayer::on_pushButton_5_clicked()
{
    player.setMedia("https://sh-btfs.ftn.qq.com/ftn_handler/5879e136d593f8643001cf6b15ab57fed6753c878a944535b5fa7d1ed3555ea9c9a389164d98d98ab1b8e2a5b2c5d0f1a86eeb80032a83d4624e493b2886f049/?fname=1.mp3&k=5c653234094dc1cb5b0ff57e1434011b5700510d025257064b5c01020519075057551f550a50011950545402010452055f04575032313305480842073209&code=fe242434&fr=00&&txf_fid=620f8eabcd02d94c83c1aa61ad476349df8c2aef&xffz=886469");
    player.play();
}

void TestPlayer::slotBufferStatusChanged(int percentFilled)
{
    qDebug() << "now:" << percentFilled;
}

void TestPlayer::on_pushButton_6_clicked()
{
    QMediaContent content = player.player->media();

    qDebug() << content.canonicalUrl();
    qDebug() << content.canonicalRequest().url();


}

void TestPlayer::slotStateChanged(QMediaPlayer::State state)
{
    qDebug() << state;
}

void TestPlayer::slotMediaStatusChanged(QMediaPlayer::MediaStatus mediaState)
{
    qDebug() << mediaState;
}
