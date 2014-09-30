#include "ComplexMovement.h"

using namespace Chess::GameLogic::Movements;

ComplexMovement::ComplexMovement( Board* const board = 0,
                                  const vector< Movement* >& moves = vector< Movement* >() )//I hope this is  an empty vector,
                                                                                    //doesn't work the Gope way
    : Movement( board ),
      m_undoMoves( moves )
{
}

ComplexMovement::~ComplexMovement()
{
    cout << "~ComplexMovement()\n";
    for ( auto iter = m_undoMoves.begin(); iter != m_undoMoves.end(); ++ iter )
    {
        delete *iter;
    }
}

bool ComplexMovement::doMove()
{
    for ( auto i = m_undoMoves.begin(); i != m_undoMoves.end(); ++ i )
    {
        ( *i )->doMove();
    }
    return true;
}

bool ComplexMovement::undoMove()
{
    for ( int i = m_undoMoves.size() - 1; i >= 0 ; -- i )
    {
       m_undoMoves[ i ]->undoMove();
       delete m_undoMoves[ i ];
    }
    return true;
}

void ComplexMovement::pushMove( Movement* move )
{
    m_undoMoves.push_back( move );
}

Movement* ComplexMovement::popMove()
{
    Movement* tmp = m_undoMoves.back();
    m_undoMoves.pop_back();
    return tmp;
}
