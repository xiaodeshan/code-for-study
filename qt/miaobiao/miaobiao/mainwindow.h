#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getSecText();

    int sec;

    QTimer timer;

public slots:
    void slotTimeOut();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
