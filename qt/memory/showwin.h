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

    void initUi();
    void showImageAndLabel(QString path, QString text, bool ispic);

    QLabel* imageLabel;
    QLabel* numLabel;
signals:

public slots:
};

#endif // SHOWWIN_H
