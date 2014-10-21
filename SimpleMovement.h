#ifndef SIMPLEMOVEMENT_H
#define SIMPLEMOVEMENT_H

#include "Movement.h"
#include "Position.h"
#include <QDebug>
#include <QVector>

using namespace std;

namespace Chess {
namespace ChessComponents {
namespace PlayField {
    class Board;
}

}

namespace GameLogic {
namespace Movements {

using namespace Chess::ChessComponents::ChessPieces;
using namespace Chess::ChessComponents::PlayField;

class SimpleMovement : public Movement
{
public:
    SimpleMovement( Board* const board,
                    const Position& from = Position( 0, 0 ),
                    const Position& to   = Position( 0, 1 ),
                    MovementFlags flags = NORMALMOVE_FLAG );
    virtual ~SimpleMovement();

    virtual bool doMove();
    virtual bool undoMove();

    virtual QString toChessNotation();

    void setFrom( const Position& from );
    Position from() const;

    void setTo( const Position& to );
    Position to() const;

    void setBoard( Board* board );
    Board* board() const;

private:
    Position                m_from;
    Position                m_to;
//    QVector< ChessPiece* > m_capturedPieces;
};

}
}
}

#endif // SIMPLEMOVEMENT_H
