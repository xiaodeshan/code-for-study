#ifndef TRAINWIN_H
#define TRAINWIN_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <QVBoxLayout>
#include <QStack>
class TrainWin : public QWidget
{
    Q_OBJECT
public:
    explicit TrainWin(QWidget *parent = nullptr);

    QLabel *phoneLabel;

    void init();
    void initUI();
    QString randomPhone();
    void nextShow();
    bool lastShow();

    QString currPhone;
    QStack<QString> backStack;


signals:

public slots:
};

#endif // TRAINWIN_H
