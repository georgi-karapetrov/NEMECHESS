#include "Visitor.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "EnPassantPawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

using namespace Chess::ChessComponents::ChessPieces;
using namespace Chess::GameLogic::GameComponents;

Visitor::Visitor()
    : m_movesStack( 0 )
{
}

Visitor::~Visitor()
{
}

void Visitor::setMovesStack( QStack< Movement* >* movementStack )
{
    m_movesStack = movementStack;
}

QStack< Movement* >* Visitor::movesStack() const
{
    return m_movesStack;
}
