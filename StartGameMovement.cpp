#include "StartGameMovement.h"

using namespace Chess::GameLogic::Movements;

StartGameMovement::StartGameMovement( Board* const board )
    : Movement( board )
{
}

bool StartGameMovement::doMove()
{
    return true;
}

bool StartGameMovement::undoMove()
{
    return true;
}

QString StartGameMovement::toChessNotation()
{
    return QString( "Game started" );
}
