#include "Widget.h"
#include <QApplication>

#include "Board.h"
#include "GameEngine.h"

using namespace Chess;
using namespace Chess::GameLogic::GameComponents;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Board board( 8, 8, 50, 50 );
    GameEngine engine;
    engine.setStandardGame();
    Widget w( engine.board() );
    w.setFixedSize( engine.board()->cellWidth() * engine.board()->columns() + 50,
                    engine.board()->cellHeight() * engine.board()->rows() + 50 );
    w.show();

    return a.exec();
}
