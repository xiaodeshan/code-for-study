#ifndef TIMERLABEL_H
#define TIMERLABEL_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>

class TimerLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TimerLabel(QWidget *parent = nullptr);

    int sec;

    void start();
    void stop();
    void reset();

    QString getSecText();
    QTimer* timer;

signals:

public slots:
    void slotTimeOut();
};

#endif // TIMERLABEL_H
