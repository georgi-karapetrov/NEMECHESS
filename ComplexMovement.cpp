#include "ComplexMovement.h"

using namespace Chess::GameLogic::Movements;

ComplexMovement::ComplexMovement( Board* const board = 0,
                                  const vector< Movement* >& moves = vector< Movement* >(),
                                  MovementFlags flags)//I hope this is  an empty vector,
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
    for ( auto i = m_movesHeap.begin(); i != m_movesHeap.end(); ++ i )
    {
        ( *i )->doMove();
    }
    return true;
}

bool ComplexMovement::undoMove()
{
    for ( int i = m_movesHeap.size() - 1; i >= 0 ; -- i )
    {
       m_movesHeap[ i ]->undoMove();
       delete m_movesHeap[ i ];
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
