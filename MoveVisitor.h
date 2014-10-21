#ifndef MOVEVISITOR_H
#define MOVEVISITOR_H

#include "Visitor.h"
#include <QDebug>

namespace Chess{

namespace ChessComponents{
namespace ChessPieces {

class ChessPiece;
class Pawn;
class EnPassantPawn;

}
}

namespace GameLogic {
namespace GameComponents{


class MoveVisitor : public Visitor
{
public:
    MoveVisitor();
    virtual ~MoveVisitor();

    virtual void visit( Chess::ChessComponents::ChessPieces::ChessPiece    *chessPiece );
    virtual void visit( Chess::ChessComponents::ChessPieces::Pawn          *pawn );
    virtual void visit( Chess::ChessComponents::ChessPieces::EnPassantPawn *enPassantPawn );
    virtual void visit( Chess::ChessComponents::ChessPieces::Rook          *rook );
    virtual void visit( Chess::ChessComponents::ChessPieces::Knight        *knight );
    virtual void visit( Chess::ChessComponents::ChessPieces::Bishop        *bishop );
    virtual void visit( Chess::ChessComponents::ChessPieces::Queen         *queen );
    virtual void visit( Chess::ChessComponents::ChessPieces::King          *king );

    void setEnPassantHappened( bool enPassantHappened );
    bool enPassantHappened() const;

private:
    bool m_enPassantHappened;
};

}
}
}
#endif // MOVEVISITOR_H
