#include "Widget.h"
#include <QApplication>

#include "Board.h"

using namespace Chess;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Board board( 8, 8, 50, 50 );

    Widget w( &board );
    w.setFixedSize( board.cellWidth() * board.columns() + 50, board.cellHeight() * board.rows() + 50 );
    w.show();

    return a.exec();
}
