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

    virtual void visit( Chess::ChessComponents::ChessPieces::ChessPiece    *chessPiece, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Pawn          *pawn, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::EnPassantPawn *enPassantPawn, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Rook          *rook, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Knight        *knight, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Bishop        *bishop, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::Queen         *queen, const Position& to );
    virtual void visit( Chess::ChessComponents::ChessPieces::King          *king, const Position& to );

    void setEnPassantHappened( bool enPassantHappened );
    bool enPassantHappened() const;

private:
    void createAndExecuteNormalMove( ChessPiece* chessPiece , const Position& to );

private:
    bool m_enPassantHappened;
};

}
}
}
#endif // MOVEVISITOR_H
