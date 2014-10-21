#include "ChessPiece.h"
#include "Visitor.h"

using namespace Chess;
using namespace Chess::GameLogic::GameComponents;
using namespace Chess::ChessComponents::ChessPieces;

ChessPiece::ChessPiece( const Position& position,
                        const Colour& colour,
                        Board* board,
                        const char sigil )
    : m_position( position ),
      m_colour( colour ),
      m_sigil( sigil )
{
    m_board = board;
}

ChessPiece::~ChessPiece()
{
    cout << "~ChessPiece()\n";
    m_board = 0;
}

void ChessPiece::setPosition( const Position& position )
{
    m_position = position;
}

Position ChessPiece::position() const
{
    return m_position;
}

void ChessPiece::setColour( const Colour& colour )
{
    m_colour = colour;
}

Colour ChessPiece::colour() const
{
    return m_colour;
}


void ChessPiece::setBoard( Board *board )
{
    m_board = board;
}

Board* ChessPiece::board() const
{
    return m_board;
}
