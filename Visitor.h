#ifndef VISITOR_H
#define VISITOR_H

#include <QDebug>
#include <QStack>
#include "Movement.h"
#include "SimpleMovement.h"
#include "ComplexMovement.h"

using namespace Chess::GameLogic::Movements;

namespace Chess{

namespace ChessComponents{
namespace ChessPieces{

class ChessPiece;
class Pawn;
class EnPassantPawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;

}
}

namespace GameLogic {
namespace GameComponents{

class Visitor
{
public:
    Visitor();
    virtual ~Visitor();

    virtual void visit( Chess::ChessComponents::ChessPieces::ChessPiece    *chessPiece, const Position& to )    = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Pawn          *pawn, const Position& to )          = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::EnPassantPawn *enPassantPawn, const Position& to ) = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Rook          *rook, const Position& to )          = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Knight        *knight, const Position& to )        = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Bishop        *bishop, const Position& to )        = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Queen         *queen, const Position& to )         = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::King          *king, const Position& to )          = 0;

    void setMovesStack( QStack< Movement* >* movementStack );
    QStack< Movement* >* movesStack() const;

protected:
    QStack< Movement* >* m_movesStack;
};

}
}
}


#endif // VISITOR_H
