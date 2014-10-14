#include "Rook.h"
#include "Board.h"

using namespace std;
//using Chess::ChessPieceType;
using namespace Chess::ChessComponents::ChessPieces;

Rook::Rook( const Position& position, const Colour& colour, Board* const board )
    : ChessPiece( position, colour, board, 'R' )
{
}

Rook::~Rook()
{
    cout << "~Rook()\n";
}

bool Rook::takes( const Position& position )
{
    return ( m_board->isPiece( position ) )
             && ( ( position.x() == m_position.x() )
                  ^ ( position.y() == m_position.y() ) );
}

QVector< Position > Rook::allowedMovements()
{
    //this is what I call cannon power...
    //although a usual cannon would blast through several enemies
    //these babes are fabriqued in China and can decimate a single target only

    //but it flies!!1

    QVector< Position > tmp;
    int x;
    int y;

    Position tmpPosition;

    for ( x = m_position.x() + 1; x < m_board->columns(); ++ x )
    {
        tmpPosition = Position( x, m_position.y() );
        if ( m_board->isPiece( tmpPosition) )
        {
            break;
        }

        tmp.push_back( tmpPosition );
    }
    if ( m_board->isPiece( tmpPosition )
         && !m_board->isAlly( tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    for ( x = m_position.x() - 1; x >= 0; -- x )
    {
        tmpPosition = Position( x, m_position.y() );
        if ( m_board->isPiece( tmpPosition ) )
        {
            break;
        }

        tmp.push_back( tmpPosition );
    }
    if ( m_board->isPiece( tmpPosition )
         && !m_board->isAlly( tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    for ( y = m_position.y() - 1; y >= 0; -- y )
    {
        tmpPosition = Position( m_position.x(), y );
        if ( m_board->isPiece( tmpPosition ) )
        {
            break;
        }

        tmp.push_back( tmpPosition );
    }
    if ( m_board->isPiece( tmpPosition )
         && !m_board->isAlly(  tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    for ( y = m_position.y() + 1; y < m_board->rows(); ++ y )
    {
        tmpPosition = Position( m_position.x(), y );
        if ( m_board->isPiece( tmpPosition ) )
        {
            break;
        }

        tmp.push_back( tmpPosition );
    }
    if ( m_board->isPiece( tmpPosition )
         && !m_board->isAlly( tmpPosition, m_colour ) )
    {
        tmp.push_back( tmpPosition );
    }

    return tmp;
}

ChessPieceType Rook::pieceType()
{
    return ROOK_TYPE;
}



