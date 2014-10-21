#ifndef VISITOR_H
#define VISITOR_H

#include <QDebug>

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

    virtual void visit( Chess::ChessComponents::ChessPieces::ChessPiece    *chessPiece )    = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Pawn          *pawn )          = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::EnPassantPawn *enPassantPawn ) = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Rook          *rook )          = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Knight        *knight )        = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Bishop        *bishop )        = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::Queen         *queen )         = 0;
    virtual void visit( Chess::ChessComponents::ChessPieces::King          *king )          = 0;
};

}
}
}


#endif // VISITOR_H
