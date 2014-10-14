#ifndef PAWN_H
#define PAWN_H

#include <cmath>
#include <QVector>
#include "ChessPiece.h"
#include "Board.h"

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

private:
    bool canAddToMovements( const Position& position ) const;

private:
    Position m_initialPosition;
};

}
}
}

#endif // PAWN_H
