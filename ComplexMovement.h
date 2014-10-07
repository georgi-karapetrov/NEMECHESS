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
                     const vector< Movement* >& moves );
    virtual ~ComplexMovement();

    virtual bool doMove();
    virtual bool undoMove();

    virtual QString toChessNotation( MovementFlags flags = NO_FLAG );

    void pushMove( Movement* move );
    Movement* popMove();

private:
    vector< Movement* > m_movesHeap;
};

}
}
}

#endif // COMPLEXMOVEMENT_H
