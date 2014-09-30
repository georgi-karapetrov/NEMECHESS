#include "Widget.h"
#include <QApplication>

#include "Board.h"
#include "GameEngine.h"

using namespace Chess;
using namespace Chess::GameLogic::GameComponents;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameEngine engine;
    engine.run();

    return a.exec();
}
