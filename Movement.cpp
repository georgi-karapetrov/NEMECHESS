#include "Movement.h"
#include "Board.h"

using namespace Chess::GameLogic::Movements;

Movement::Movement( Board* const board , MovementFlags flags )
    : m_board( board ),
      m_flags( flags )
{
}

Movement::~Movement()
{
    cout << "~Movement()\n";
}

void Movement::setFlags( const MovementFlags& flags )
{
    m_flags = flags;
}

Chess::MovementFlags Movement::flags() const
{
    return m_flags;
}
