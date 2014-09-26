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
    return ( m_board->isValidPosition( position ) )
             && ( ( position.x() == m_position.x() )
                  ^ ( position.y() == m_position.y() ) );
}

vector< Position > Rook::allowedMovements()
{
    //this is what I call cannon power...
    //although a usual cannon would blast through several enemies
    //these babes are fabriqued in China and can decimate a single target only

    //but it flies!!1

    vector< Position > tmp;
    int x;
    int y;

    for ( x = m_position.x() + 1; x < m_board->columns(); ++ x )
    {        if ( m_board->isPiece( Position ( x, m_position.y() ) ) )
        {
            break;
        }

        tmp.push_back( Position( x, m_position.y() ) );
    }
    if ( !m_board->isObstacle(  Position ( x, m_position.y() ), m_colour ) )
    {
        tmp.push_back( Position( x, m_position.y() ) );
    }

    for ( x = m_position.x() - 1; x >= 0; -- x )
    {
        if ( m_board->isPiece( Position ( x, m_position.y() ) ) )
        {
            break;
        }

        tmp.push_back( Position( x, m_position.y() ) );
    }
    if ( !m_board->isObstacle(  Position ( x, m_position.y() ), m_colour ) )
    {
        tmp.push_back( Position( x, m_position.y() ) );
    }

    for ( y = m_position.y() - 1; y >= 0; -- y )
    {
        if ( m_board->isPiece( Position ( m_position.x(), y ) ) )
        {
            break;
        }

        tmp.push_back( Position( m_position.x(), y ) );
    }
    if ( !m_board->isObstacle(  Position ( m_position.x(), y ), m_colour ) )
    {
        tmp.push_back( Position ( m_position.x(), y ) );
    }

    for ( y = m_position.y() + 1; y < m_board->rows(); ++ y )
    {
        if ( m_board->isPiece( Position ( m_position.x(), y ) ) )
        {
            break;
        }

        tmp.push_back( Position( m_position.x(), y ) );
    }
    if ( !m_board->isObstacle(  Position ( m_position.x(), y ), m_colour ) )
    {
        tmp.push_back( Position ( m_position.x(), y ) );
    }

    return tmp;
}

ChessPieceType Rook::pieceType()
{
    return ROOK_TYPE;
}
