#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("World Of Warplanes");

    Game::initialise(&a);
    Game::getInstance().show();

    return a.exec();
}
