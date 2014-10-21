#include "MoveVisitor.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "EnPassantPawn.h"

using namespace Chess::GameLogic::GameComponents;
using namespace Chess::ChessComponents::ChessPieces;

MoveVisitor::MoveVisitor()
    : m_enPassantHappened( false )
{
}

MoveVisitor::~MoveVisitor()
{
}

void MoveVisitor::visit( ChessPiece* chessPiece )
{
    qDebug() << "MoveVisitor::visit( ChessPiece )";
    Q_UNUSED( chessPiece );
}

void MoveVisitor::visit( Pawn* pawn )
{
    qDebug() << "MoveVisitor::visit( Pawn )";
    m_enPassantHappened = false;
    if ( pawn->enPassantPawn() != 0 )
    {
        pawn->board()->removePiece( pawn->enPassantPawn() );
    }
    if ( pawn->position() == Position( pawn->initialPosition().x(), pawn->initialPosition().y() + 2 * pawn->offset() ) )
    {
        pawn->makeEnPassant();
        m_enPassantHappened = true;
    }
}

void MoveVisitor::visit( EnPassantPawn* enPassantPawn )
{
    qDebug() << "MoveVisitor::visit( EnPassantPawn )";
    Q_UNUSED( enPassantPawn );
}

void MoveVisitor::visit( Rook* rook )
{
    qDebug() << "MoveVisitor::visit( Rook )";
    m_enPassantHappened = false;
    Q_UNUSED( rook );
}

void MoveVisitor::visit( Knight* knight )
{
    qDebug() << "MoveVisitor::visit( Knight )";
    m_enPassantHappened = false;
    Q_UNUSED( knight );
}

void MoveVisitor::visit( Bishop* bishop )
{
    qDebug() << "MoveVisitor::visit( Bishop )";
    m_enPassantHappened = false;
    Q_UNUSED( bishop );
}

void MoveVisitor::visit( Queen* queen )
{
    qDebug() << "MoveVisitor::visit( Queen )";
    m_enPassantHappened = false;
    Q_UNUSED( queen );
}
void MoveVisitor::visit( King* king )
{
    qDebug() << "MoveVisitor::visit( King )";
    m_enPassantHappened = false;
    Q_UNUSED( king );
}

void MoveVisitor::setEnPassantHappened( bool enPassantHappened )
{
    m_enPassantHappened = enPassantHappened;
}

bool MoveVisitor::enPassantHappened() const
{
    return m_enPassantHappened;
}
