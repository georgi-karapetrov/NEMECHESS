#include "ComplexMovement.h"

using namespace Chess::GameLogic::Movements;

ComplexMovement::ComplexMovement( Board* const board,
                                  const QVector< Movement* >& moves,
                                  MovementFlags flags)//I hope this is  an empty QVector,
                                                                                    //doesn't work the Gope way
    : Movement( board, flags ),
      m_movesHeap( moves )
{
}

ComplexMovement::~ComplexMovement()
{
    cout << "~ComplexMovement()\n";
    for ( auto iter = m_movesHeap.begin(); iter != m_movesHeap.end(); ++ iter )
    {
        delete *iter;
    }
}

bool ComplexMovement::doMove()
{
    for ( auto iter = m_movesHeap.begin(); iter != m_movesHeap.end(); ++ iter )
    {
        ( *iter )->doMove();
    }
    return true;
}

bool ComplexMovement::undoMove()
{
    for ( int iter = m_movesHeap.size() - 1; iter >= 0 ; -- iter )
    {
       m_movesHeap[ iter ]->undoMove();
  //     delete m_movesHeap[ i ];
    }
    return true;
}

void ComplexMovement::pushMove( Movement* move )
{
    m_movesHeap.push_back( move );
}

Movement* ComplexMovement::popMove()
{
    Movement* tmp = m_movesHeap.back();
    m_movesHeap.pop_back();
    return tmp;
}

QString ComplexMovement::toChessNotation()
{
    switch ( m_flags )
    {
    case KINGSIDECASTLING_FLAG:
        return "0-0";
    case QUEENSIDECASTLING_FLAG:
        return "0-0-0";
    default:
        return "Unknown Complex move";
    }
}
