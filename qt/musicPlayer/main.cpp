#include <QApplication>
#include <QDebug>

#include "generalplayer.h"
#include "testplayer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

    TestPlayer testPlayer;

    testPlayer.show();

    return a.exec();
}
