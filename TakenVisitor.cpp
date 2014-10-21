#include "TakenVisitor.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "EnPassantPawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

using namespace Chess::GameLogic::GameComponents;
using namespace Chess::ChessComponents::ChessPieces;

TakenVisitor::TakenVisitor()
    : m_capturedPieces( 0 )
{
}

TakenVisitor::~TakenVisitor()
{
}


void TakenVisitor::visit( ChessPiece* chessPiece, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( ChessPiece )";
    Q_UNUSED( chessPiece );
}

void TakenVisitor::visit( Pawn* pawn, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( Pawn )";

    if ( pawn->enPassantPawn() != 0 )
    {
        m_capturedPieces->push( pawn->enPassantPawn() );
    }

//    pawn->board()->removePiece( pawn ); // failproof? - NO
    m_capturedPieces->push( pawn );
}

void TakenVisitor::visit( EnPassantPawn* enPassantPawn, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( EnPassantPawn )";

    enPassantPawn->board()->removePiece( enPassantPawn->pawn() );
 //   enPassantPawn->board()->removePiece( enPassantPawn );

    m_capturedPieces->push( enPassantPawn );
    m_capturedPieces->push( enPassantPawn->pawn() );
}

void TakenVisitor::visit( Rook* rook, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( Rook )";
    m_capturedPieces->push(rook );
}

void TakenVisitor::visit( Knight* knight, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( Knight )";
    m_capturedPieces->push( knight );
}

void TakenVisitor::visit( Bishop* bishop, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( Bishop )";
    m_capturedPieces->push( bishop );
}

void TakenVisitor::visit( Queen* queen, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( Queen )";
    m_capturedPieces->push( queen );
}
void TakenVisitor::visit( King* king, const Position& to )
{
    Q_UNUSED( to );
    qDebug() << "TakenVisitor::visit( King )";
    m_capturedPieces->push( king );
}

void TakenVisitor::setCapturedPieces( QStack< ChessPiece* >* capturedPieces )
{
    m_capturedPieces = capturedPieces;
}

QStack< ChessPiece* >* TakenVisitor::capturedPieces() const
{
    return m_capturedPieces;
}
