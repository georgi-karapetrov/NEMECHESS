#ifndef STARTGAMEMOVEMENT_H
#define STARTGAMEMOVEMENT_H

#include "Movement.h"
#include "Position.h"
#include <QString>

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

class StartGameMovement : public Movement
{

public:
    StartGameMovement( Board* const board );

    virtual bool doMove();
    virtual bool undoMove();

    virtual QString toChessNotation();
};

}
}
}

#endif // STARTGAMEMOVEMENT_H
