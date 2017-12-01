#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "memorymain.h"
#include "memorymain.h"
#define CARD_PATH ":/images/image/"
#define CARD_NAME_PATH ":/raw/raw/names.txt"
namespace Ui {
class MainWindow;
}

class MemoryMain;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MemoryMain *memoryMain;

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
