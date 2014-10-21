#include "Pawn.h"

#include "Visitor.h"

using namespace std;
using namespace Chess::ChessComponents::ChessPieces;

Pawn::Pawn( const Position& position, const Colour& colour, Board* board )
    : ChessPiece( position, colour, board, 'P' ),
      m_initialPosition( position ),
      m_enPassantPawn( 0 )
{
    m_offset = m_colour == white ? -1 : +1;
}

Pawn::~Pawn()
{
    cout << "~Pawn()\n";
}

bool Pawn::takes( const Position& position )
{
    const int offset = m_colour == white ? +1 : -1;

    return m_board->isValidPosition( position )
            && ( abs( m_position.x() - position.x() ) == 1
                 && ( m_position.y() - position.y() == offset ) );
}

QVector< Position > Pawn::allowedMovements()
{
    QVector< Position > result;

    const int offset = m_colour == white ? -1 : +1;

    //maybe if they got paid more they'd do more than move one step forward...
    //and stop if there's a fat guy in front of them



    if ( m_board->isValidPosition( Position( m_position.x(), m_position.y() + offset ) )
         && !m_board->isPiece( Position( m_position.x(), m_position.y() + offset ) ) )
    {
        result.push_back( Position( m_position.x(), m_position.y() + offset ) );
    }

    if ( m_position == m_initialPosition
         && m_board->isValidPosition( Position( m_position.x(), m_position.y() + offset * 2 ) )
         && ! m_board->isPiece( Position( m_position.x(), m_position.y() + offset * 2 ) ) )
    {
        result.push_back( Position( m_position.x(), m_position.y() + offset * 2 )  );
    }

    if ( this->canAttackAt( Position( m_position.x() + 1, m_position.y() + offset ) ) )
    {
        result.push_back( Position( m_position.x() + 1, m_position.y() + offset ) );
    }

    if ( this->canAttackAt( Position( m_position.x() - 1, m_position.y() + offset ) ) )
    {
        result.push_back( Position( m_position.x() - 1, m_position.y() + offset ) );
    }

    return result;
}

void Pawn::setInitialPosition( const Position& position )
{
    m_initialPosition = position;
}

Position Pawn::initialPosition() const
{
    return m_initialPosition;
}

bool Pawn::canAttackAt( const Position& position ) const
{
    bool validPos = m_board->isValidPosition( position );
    bool piece    = m_board->isPiece( position );
    bool obstacle = m_board->isAlly( position, m_colour );

    return validPos && piece && !obstacle;
}

ChessPieceType Pawn::pieceType()
{
    return PAWN_TYPE;
}

void Pawn::makeEnPassant()
{
    m_enPassantPawn = new EnPassantPawn( Position( m_position.x(), m_position.y() - m_offset ), this );
    m_board->addPiece( m_enPassantPawn );
}

EnPassantPawn* Pawn::enPassantPawn()
{
    return m_enPassantPawn;
}

bool Pawn::isEnPassant()
{
    return m_enPassantPawn != 0;
}

int Pawn::offset() const
{
    return m_offset;
}

void Pawn::accept( Visitor& visitor )
{
    visitor.visit( this );
}
