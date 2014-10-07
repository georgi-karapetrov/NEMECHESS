#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <unordered_map>
#include <QString>

namespace Chess{

enum MovementFlagsEnum
{
    NO_FLAG        = 0,
    CASTLING_FLAG  = 1,
    CHECK_FLAG     = 2,
    POWERMOVE_FLAG = 4
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
    Movement( Board* const board = 0 );
    virtual ~Movement();

    virtual bool doMove() = 0;
    virtual bool undoMove() = 0;

    virtual QString toChessNotation( MovementFlags flags = NO_FLAG ) = 0;

protected:
    Board* m_board;

};

}
}
}

#endif // MOVEMENT_H
