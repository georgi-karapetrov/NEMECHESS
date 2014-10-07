#include "Movement.h"
#include "Board.h"

using namespace Chess::GameLogic::Movements;

Movement::Movement( Board* const board )
    : m_board( board )
{
}

Movement::~Movement()
{
    cout << "~Movement()\n";
}

// TODO: move toChessNotation() functionality here #OK
//       create flags for the moves #OK
//       connect the model and the movement collection
