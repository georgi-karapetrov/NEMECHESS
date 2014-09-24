#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "Position.h"

#include <algorithm>
#include <stack>
#include <vector>

namespace Chess{

    enum Colour //not racist
    {
        white = 0,
        black = 1
    };


namespace ChessComponents {
namespace PlayField {
    class Board;
}

namespace ChessPieces {

using std::vector;
using std::unordered_map;
using std::stack;

using namespace Chess::ChessComponents::PlayField;

enum ChessPieceType
{
    PAWN_TYPE   = 0,
    ROOK_TYPE   = 1,
    KNIGHT_TYPE = 2,
    BISHOP_TYPE = 3,
    QUEEN_TYPE  = 4,
    KING_TYPE   = 5
};

inline Colour nextColour( const Colour& colour )
{
    return colour == white ? black : white;
}

class ChessPiece
{
public:
    ChessPiece( const Position& position = Position( 0, 0 ),
                const Colour& colour     = white,
                Board* board             = 0,
                const char sigil         = '.' );
    virtual ~ChessPiece();

    virtual void setPosition( const Position& position );
    Position position() const;

    virtual bool takes( const Position& position ) = 0;
    virtual vector< Position > allowedMovements() = 0;

    void setColour( const Colour& colour );
    Colour colour() const;

    virtual ChessPieceType pieceType() = 0;

protected:
    Position     m_position;
    Colour       m_colour;
    const Board* m_board;

public:
    char         m_sigil;
};

}
}
}

#endif // CHESSPIECE_H
