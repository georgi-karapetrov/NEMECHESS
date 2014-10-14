#ifndef COMPLEXMOVEMENT_H
#define COMPLEXMOVEMENT_H

#include "Movement.h"
#include "SimpleMovement.h"
#include <vector>

namespace Chess{
namespace GameLogic{
namespace Movements{

class SimpleMovement;

class ComplexMovement : public Movement
{
public:
    ComplexMovement( Board* const board,
                     const vector< Movement* >& moves,
                     MovementFlags flags = KINGSIDECASTLING_FLAG );
    virtual ~ComplexMovement();

    virtual bool doMove();
    virtual bool undoMove();

    virtual QString toChessNotation();

    void pushMove( Movement* move );
    Movement* popMove();

private:
    vector< Movement* > m_movesHeap;
};

}
}
}

#endif // COMPLEXMOVEMENT_H
