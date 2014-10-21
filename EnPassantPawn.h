#ifndef ENPASSANTPAWN_H
#define ENPASSANTPAWN_H

#include "ChessPiece.h"

#include <QDebug>

namespace Chess{
namespace ChessComponents{
namespace ChessPieces{

class Pawn;

class EnPassantPawn : public ChessPiece
{
public:
    EnPassantPawn( const Position& position, ChessPiece* pawn );
    ~EnPassantPawn();

    void setPawn( ChessPiece* pawn );
    ChessPiece* pawn() const;

    virtual bool takes( const Position& position );
    virtual QVector< Position > allowedMovements();
    virtual ChessPieceType pieceType();

    virtual void accept( Visitor& visitor, const Position& to );

private:
    ChessPiece* m_pawn;
};

}
}
}

#endif // ENPASSANTPAWN_H
