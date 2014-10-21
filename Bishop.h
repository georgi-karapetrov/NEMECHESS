#ifndef BISHOP_H
#define BISHOP_H

#include <QVector>
#include "ChessPiece.h"

namespace Chess{
namespace ChessComponents{
namespace ChessPieces{

class Bishop : public ChessPiece
{
public:
    Bishop( const Position& position, const Colour& colour, Board* const board );

    ~Bishop();

    bool takes( const Position& position );
    virtual QVector< Position > allowedMovements();

    ChessPieceType pieceType();

    virtual void accept(Visitor& visitor, const Position& to );

};

}
}
}

#endif // BISHOP_H
