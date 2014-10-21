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

    virtual void visit( Chess::ChessComponents::ChessPieces::ChessPiece*    chessPiece, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Pawn*          pawn, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::EnPassantPawn* enPassantPawn, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Rook*          rook, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Knight*        knight, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Bishop*        bishop, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Queen*         queen, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::King*          king, const Position& to );

    void setCapturedPieces(QStack<ChessComponents::ChessPieces::ChessPiece *>* capturedPieces );
    QStack<ChessComponents::ChessPieces::ChessPiece *> *capturedPieces() const;

private:
    QStack< Chess::ChessComponents::ChessPieces::ChessPiece* >* m_capturedPieces;
};

}
}
}

#endif // TAKENVISITOR_H
