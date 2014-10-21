#ifndef COMPLEXMOVEMENT_H
#define COMPLEXMOVEMENT_H

#include "Movement.h"
#include "SimpleMovement.h"
#include <QVector>

namespace Chess{
namespace GameLogic{
namespace Movements{

class SimpleMovement;

class ComplexMovement : public Movement
{
public:
    ComplexMovement( Board* const board,
                     const QVector< Movement* >& moves  = QVector< Movement* >(),
                     MovementFlags flags = KINGSIDECASTLING_FLAG );
    virtual ~ComplexMovement();

    virtual bool doMove();
    virtual bool undoMove();

    virtual QString toChessNotation();

    void pushMove( Movement* move );
    Movement* popMove();

private:
    QVector< Movement* > m_movesHeap;
};

}
}
}

#endif // COMPLEXMOVEMENT_H
