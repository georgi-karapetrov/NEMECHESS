#include "Bishop.h"
#include "Board.h"

#include "Visitor.h"

using namespace std;
//using Chess::ChessPieceType;
using namespace Chess::ChessComponents::ChessPieces;

Bishop::Bishop(const Position& position, const Colour& colour, Board* const board )
    : ChessPiece( position, colour, board, 'B' )
{
}

Bishop::~Bishop()
{
    cout << "~Bishop()\n";
}

bool Bishop::takes( const Position& position )
{
   return m_board->isValidPosition( position ) &&
          position.x() - m_position.x() == position.y() - m_position.y();
}

QVector<Position> Bishop::allowedMovements()
{
    QVector< Position > tmp;
    int i = 1;

    //these bishops' religion prohibits them from moving over obstacles
    //from what I've heard, however, they're hardly obstructed by little children...
    //little boys, especially...

    Position tmpPosition = Position( m_position.x() + i, m_position.y() + i );

    //+, +
    while ( m_board->isValidPosition( tmpPosition )
            && !m_board->isPiece( tmpPosition ) )
    {
        tmp.push_back( tmpPosition );
        ++ i;
        tmpPosition = Position( m_position.x() + i, m_position.y() + i );
    }
    if ( m_board->isValidPosition( tmpPosition )
         &&  m_board->isPiece( tmpPosition )
         && !m_board->isAlly( tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    //+, -
    i = 1;
    tmpPosition = Position( m_position.x() + i, m_position.y() - i );
    while ( m_board->isValidPosition( tmpPosition )
            && !m_board->isPiece( tmpPosition ) )
    {
        tmp.push_back( tmpPosition );
        ++ i;
        tmpPosition = Position( m_position.x() + i, m_position.y() - i );
    }
    if ( m_board->isValidPosition( tmpPosition )
         &&  m_board->isPiece( tmpPosition )
         && !m_board->isAlly( tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    //-, +
    i = 1;
    tmpPosition = Position( m_position.x() - i, m_position.y() + i );
    while ( m_board->isValidPosition( tmpPosition )
            && !m_board->isPiece( tmpPosition ) )
    {
        tmp.push_back( tmpPosition );
        ++ i;
        tmpPosition = Position( m_position.x() - i, m_position.y() + i );
    }
    if ( m_board->isValidPosition( tmpPosition )
         &&  m_board->isPiece( tmpPosition )
         && !m_board->isAlly( tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    //-, -
    i = 1;
    tmpPosition = Position( m_position.x() - i, m_position.y() - i );
    while ( m_board->isValidPosition( tmpPosition )
            && !m_board->isPiece( tmpPosition ) )
    {
        tmp.push_back( tmpPosition );
        ++ i;
        tmpPosition = Position( m_position.x() - i, m_position.y() - i );
    }
    if ( m_board->isValidPosition( tmpPosition )
         &&  m_board->isPiece( tmpPosition )
         && !m_board->isAlly( tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    return tmp;
}

ChessPieceType Bishop::pieceType()
{
    return BISHOP_TYPE;
}

void Bishop::accept( Visitor& visitor )
{
    visitor.visit( this );
}
