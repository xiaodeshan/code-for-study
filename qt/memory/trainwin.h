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

    //变量
    QLabel *phoneLabel;
    QString currPhone;
    QStack<QString> backStack;

    //函数
    void init();
    void initUI();
    QString randomPhone();
    void nextShow();
    bool lastShow();

signals:

public slots:
};

#endif // TRAINWIN_H
