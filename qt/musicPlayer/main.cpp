#include "xxxwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XXXWidget w;
    w.show();

    return a.exec();
}
