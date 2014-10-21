#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

#include <QVector>


namespace Chess{
namespace ChessComponents{
namespace PlayField {
    class Board;
}

namespace ChessPieces{

class Rook : public ChessPiece
{
public:
    Rook( const Position& position = Position( 0, 0 ), const Colour& colour = white, Board* const board = 0 );
    ~Rook();

    bool takes( const Position& position );
    virtual QVector< Position > allowedMovements();

    ChessPieceType pieceType();

    virtual void accept(Visitor& visitor );
};

}
}
}

#endif // ROOK_H
