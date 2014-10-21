#ifndef KNIGHT_H
#define KNIGHT_H

#include <QVector>
#include "ChessPiece.h"

namespace Chess{
namespace ChessComponents{
namespace ChessPieces{

class Knight : public ChessPiece
{
public:
    Knight( const Position& position, const Colour& colour, Board* board );
    ~Knight();

    bool takes( const Position& position );
    virtual QVector< Position > allowedMovements();

    virtual void accept(Visitor& visitor, const Position& to );

    ChessPieceType pieceType();

private:
    void checkAllowedMovements ( const Position& position, QVector< Position >& aVector );
};

}

}

}

#endif // KNIGHT_H
