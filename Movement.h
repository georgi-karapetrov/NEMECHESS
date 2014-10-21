#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QVector>
#include <unordered_map>
#include <QString>

namespace Chess{

enum MovementFlagsEnum
{
    NO_FLAG = 0,
    NORMALMOVE_FLAG        =  1,
    KINGSIDECASTLING_FLAG  =  2,
    QUEENSIDECASTLING_FLAG =  4,
    CHECK_FLAG             =  8,
    POWERMOVE_FLAG         = 16,
    CAPTURE_FLAG           = 32
};
Q_DECLARE_FLAGS( MovementFlags, MovementFlagsEnum )
Q_DECLARE_OPERATORS_FOR_FLAGS( MovementFlags )

namespace ChessComponents {
namespace PlayField {
    class Board;
    //class ChessPiece;
}
namespace ChessPieces {
    class ChessPiece;
}
}

namespace GameLogic {
namespace Movements {

using namespace Chess::ChessComponents::PlayField;
using namespace Chess::ChessComponents::ChessPieces;

using namespace std;

class Movement
{
public:
    Movement( Board* const board = 0, MovementFlags flags = NORMALMOVE_FLAG );
    virtual ~Movement();

    virtual bool doMove() = 0;
    virtual bool undoMove() = 0;

    virtual QString toChessNotation() = 0;

    void setFlags( const MovementFlags& flags );
    MovementFlags flags() const;

    void setCapturedPiece( ChessPiece* chessPiece );
    ChessPiece* capturedPiece() const;

protected:
    Board* m_board;
    Chess::MovementFlags m_flags;
    ChessPiece* m_capturedPiece;

};

}
}
}

#endif // MOVEMENT_H
