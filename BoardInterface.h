#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H

#include <QColor>
#include <QPainter>
#include <QWidget>

#include "Board.h"
#include "Position.h"
//#include "ChessPieceInterface.h"

class ChessPieceInterface;

using namespace Chess::ChessComponents::PlayField;

class BoardInterface
{

public:
    static const int X_OFFSET;
    static const int Y_OFFSET;

public:
    BoardInterface( Board* board = 0, QWidget* parent = 0 );

    void drawBoard( QPainter& painter );

private:
    QColor alternateColour( const QColor& colour );
    void drawPosition( QPainter& painter, const Position& position, const QColor& colour );
    void drawNotationRulers( QPainter& painter );

private:
    Board*               m_board;
    ChessPieceInterface* m_chessPieceInterface;
};

#endif // BOARDINTERFACE_H
