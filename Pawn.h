#ifndef PAWN_H
#define PAWN_H

#include <cmath>
#include <QVector>
#include "ChessPiece.h"
#include "Board.h"
#include "EnPassantPawn.h"

namespace Chess{
namespace ChessComponents{
namespace ChessPieces{


class Pawn : public ChessPiece
{
public:
    Pawn( const Position& position, const Colour& Colour, Board* board );

    ~Pawn();

    bool takes( const Position& position );
    virtual QVector< Position > allowedMovements();

    void setInitialPosition( const Position& position );
    Position initialPosition() const;

    ChessPieceType pieceType();

    void makeEnPassant();

    EnPassantPawn* enPassantPawn();
    bool isEnPassant();

    void promoteTo( const ChessPieceType& newPieceType );

    int offset() const;

    virtual void accept( Visitor& visitor );

private:
    bool canAttackAt( const Position& position ) const;

private:
    int            m_offset;
    Position       m_initialPosition;
    EnPassantPawn* m_enPassantPawn;
};

}
}
}

#endif // PAWN_H
