#include "Knight.h"
#include "Board.h"

#include <cmath>
#include <algorithm>

using namespace std;
//using Chess::ChessPieceType;
using namespace Chess::ChessComponents::ChessPieces;

Knight::Knight( const Position& position, const Colour& colour, Board* board )
    : ChessPiece( position, colour, board, 'N' )
{
}

Knight::~Knight()
{
    cout << "~Knight()\n";
}

bool Knight::takes( const Position& position )
{
    return m_board->isValidPosition( position ) &&
           ( ( ( abs( m_position.x() - position.x() ) == 1 ) &&
             ( abs( m_position.y() - position.y() ) == 2 ) ) ||
           ( ( abs( m_position.x() - position.x() ) == 2 ) &&
             ( abs( m_position.y() - position.y() ) == 1 ) ) );
}

void Knight::checkAllowedMovements ( const Position& position, vector< Position >& aVector )
{
    //no one is a match for the righteous knight
    //petty obstacles cannot prevent him from jumping to his death

    if ( m_board->isValidPosition( position ) )
    {
        if ( !( m_board->isAlly( position, m_colour )
                || ( m_board->isPiece( position ) &&  m_board->pieceAt( position )->pieceType() == KING_TYPE ) ) )
        {
            aVector.push_back( position );
        }
    }
}

vector< Position > Knight::allowedMovements()
{
    vector< Position > tmp;

    checkAllowedMovements( Position( m_position.x() - 2, m_position.y() - 1 ), tmp );
    checkAllowedMovements( Position( m_position.x() - 2, m_position.y() + 1 ), tmp );
    checkAllowedMovements( Position( m_position.x() - 1, m_position.y() - 2 ), tmp );
    checkAllowedMovements( Position( m_position.x() - 1, m_position.y() + 2 ), tmp );
    checkAllowedMovements( Position( m_position.x() + 2, m_position.y() - 1 ), tmp );
    checkAllowedMovements( Position( m_position.x() + 2, m_position.y() + 1 ), tmp );
    checkAllowedMovements( Position( m_position.x() + 1, m_position.y() + 2 ), tmp );
    checkAllowedMovements( Position( m_position.x() + 1, m_position.y() - 2 ), tmp );

    return tmp;
}

ChessPieceType Knight::pieceType()
{
    return KNIGHT_TYPE;
}
