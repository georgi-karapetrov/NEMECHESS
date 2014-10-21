#include "EnPassantPawn.h"

#include "Visitor.h"

using namespace Chess::ChessComponents::ChessPieces;

EnPassantPawn::EnPassantPawn( const Position& position, ChessPiece* pawn )
    : ChessPiece( position, pawn->colour(), pawn->board(), '.' ),
      m_pawn( pawn )
{
    qDebug() << "En-passant pawn is created on" << position.x() << position.y();
}

EnPassantPawn::~EnPassantPawn()
{
    qDebug() << "En-passant pawn deleted";
}

void EnPassantPawn::setPawn( ChessPiece* pawn )
{
    m_pawn = pawn;
}

ChessPiece *EnPassantPawn::pawn() const
{
    return m_pawn;
}

bool EnPassantPawn::takes( const Position& position )
{
    Q_UNUSED( position )
    return false;
}

QVector< Position > EnPassantPawn::allowedMovements()
{
    return QVector< Position >();
}

ChessPieceType EnPassantPawn::pieceType()
{
    return ENPASSANT_PAWN_TYPE;
}

void EnPassantPawn::accept( Visitor& visitor, const Position& to )
{
    visitor.visit( this, to );
}
