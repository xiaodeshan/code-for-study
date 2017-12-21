#ifndef SHOWWIN_H
#define SHOWWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
class ShowWin : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWin(QWidget *parent = nullptr);

    //变量
    QLabel* imageLabel;
    QLabel* numLabel;

    //函数
    void initUi();
    void showImageAndLabel(QString path, QString text, bool ispic);

signals:

public slots:
};

#endif // SHOWWIN_H
