#ifndef KING_H
#define KING_H

#include <cmath>
#include <QVector>

#include "ChessPiece.h"
#include "Queen.h"

// comment

namespace Chess{
namespace ChessComponents{
namespace ChessPieces{

class King : public ChessPiece
{
public:
    King( const Position& position, const Colour& colour, Board* board );
    ~King();

    bool takes( const Position& position );
    virtual QVector< Position > allowedMovements();

    ChessPieceType pieceType();

private:
    void checkAllowedMovements( const Position& position, QVector< Position >& aVector );
    bool inCheck();
};

}
}
}

#endif // KING_H
