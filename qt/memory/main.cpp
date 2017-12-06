#include "memorymain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MemoryMain w;
    w.show();

    return a.exec();
}
