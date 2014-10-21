#ifndef TAKENVISITOR_H
#define TAKENVISITOR_H

#include "Visitor.h"

#include <QStack>

//using namespace Chess::GameLogic::GameComponents;

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


class TakenVisitor : public Visitor
{
public:
    TakenVisitor();
   virtual ~TakenVisitor();

    virtual void visit( Chess::ChessComponents::ChessPieces::ChessPiece*    chessPiece );
    virtual void visit( Chess::ChessComponents::ChessPieces::Pawn*          pawn );
    virtual void visit( Chess::ChessComponents::ChessPieces::EnPassantPawn* enPassantPawn );
    virtual void visit( Chess::ChessComponents::ChessPieces::Rook*          rook );
    virtual void visit( Chess::ChessComponents::ChessPieces::Knight*        knight );
    virtual void visit( Chess::ChessComponents::ChessPieces::Bishop*        bishop );
    virtual void visit( Chess::ChessComponents::ChessPieces::Queen*         queen );
    virtual void visit( Chess::ChessComponents::ChessPieces::King*          king );

    void setCapturedPieces(QStack<ChessComponents::ChessPieces::ChessPiece *>* capturedPieces );
    QStack<ChessComponents::ChessPieces::ChessPiece *> *capturedPieces() const;

private:
    QStack< Chess::ChessComponents::ChessPieces::ChessPiece* >* m_capturedPieces;
};

}
}
}

#endif // TAKENVISITOR_H
