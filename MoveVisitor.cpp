#include "MoveVisitor.h"
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

MoveVisitor::MoveVisitor()
    : m_enPassantHappened( false )
{
}

MoveVisitor::~MoveVisitor()
{
}

void MoveVisitor::visit( ChessPiece* chessPiece, const Position& to )
{
    qDebug() << "MoveVisitor::visit( ChessPiece )";
    Q_UNUSED( chessPiece );
    Q_UNUSED( to );
}

void MoveVisitor::visit( Pawn* pawn, const Position& to )
{
    qDebug() << "MoveVisitor::visit( Pawn )";
    m_enPassantHappened = false;
    if ( pawn->enPassantPawn() != 0 )
    {
        pawn->board()->removePiece( pawn->enPassantPawn() );
    }

    if ( to == Position( pawn->initialPosition().x(), pawn->initialPosition().y() + 2 * pawn->offset() ) )
    {
        pawn->makeEnPassant();

        QVector< Movement* > enPassantPiecesVector;
        Movement* pawnMovement = new SimpleMovement( pawn->board(), pawn->position(), to, NORMALMOVE_FLAG );

        Movement* enPassantPawnMovement = new SimpleMovement( pawn->enPassantPawn()->board(),
                                                              pawn->enPassantPawn()->position(),
                                                              pawn->enPassantPawn()->position(),
                                                              NORMALMOVE_FLAG );
        enPassantPiecesVector.push_back( pawnMovement );
        enPassantPiecesVector.push_back( enPassantPawnMovement );

        Movement* createEnPassantMovement = new ComplexMovement( pawn->board(),
                                                                 enPassantPiecesVector,
                                                                 NO_FLAG );

        enPassantPawnMovement->setCapturedPiece( pawn->enPassantPawn() );
        enPassantPawnMovement->setFlags( CAPTURE_FLAG );
        createEnPassantMovement->doMove();
        m_movesStack->push( createEnPassantMovement );
        m_enPassantHappened = true;
    }
    else
    {
        createAndExecuteNormalMove( pawn, to );
    }
}

void MoveVisitor::visit( EnPassantPawn* enPassantPawn, const Position& to )
{
    qDebug() << "MoveVisitor::visit( EnPassantPawn )";
    Q_UNUSED( enPassantPawn );
    Q_UNUSED( to );
}

void MoveVisitor::visit( Rook* rook, const Position& to )
{
    qDebug() << "MoveVisitor::visit( Rook )";
    m_enPassantHappened = false;

    createAndExecuteNormalMove( rook, to );
}

void MoveVisitor::visit( Knight* knight, const Position& to )
{
    qDebug() << "MoveVisitor::visit( Knight )";
    m_enPassantHappened = false;
    createAndExecuteNormalMove( knight, to );
}

void MoveVisitor::visit( Bishop* bishop, const Position& to  )
{
    qDebug() << "MoveVisitor::visit( Bishop )";
    m_enPassantHappened = false;
    createAndExecuteNormalMove( bishop, to );
}

void MoveVisitor::visit( Queen* queen, const Position& to  )
{
    qDebug() << "MoveVisitor::visit( Queen )";
    m_enPassantHappened = false;
    createAndExecuteNormalMove( queen, to );
}
void MoveVisitor::visit( King* king, const Position& to  )
{
    qDebug() << "MoveVisitor::visit( King )";
    m_enPassantHappened = false;
    createAndExecuteNormalMove( king, to );
}

void MoveVisitor::setEnPassantHappened( bool enPassantHappened )
{
    m_enPassantHappened = enPassantHappened;
}

bool MoveVisitor::enPassantHappened() const
{
    return m_enPassantHappened;
}

void MoveVisitor::createAndExecuteNormalMove( ChessPiece* chessPiece, const Position& to )
{
    Movement* movement = new SimpleMovement( chessPiece->board(), chessPiece->position(), to, NORMALMOVE_FLAG );
    movement->doMove();
    m_movesStack->push( movement );
}
