#ifndef PIECESMANIPULATOR_H
#define PIECESMANIPULATOR_H

#include "Board.h"
#include "ChessPiece.h"
#include "Movement.h"
#include "SimpleMovement.h"
#include "ComplexMovement.h"

#include <QDebug>

#include <QStack>

namespace Chess {
namespace ChessComponents {
namespace PlayField {
    class Board;
}
}

namespace GameLogic {
namespace GameComponents{

using namespace Chess::GameLogic::Movements;
using namespace Chess::ChessComponents::ChessPieces;

enum Error
{
    WrongColour,
    EmptyPosition,
    Success,
    InvalidDestination,
    Check,
    KingCapture,
    Castling,
    ReachedEnd
};

enum CastlingType
{
    KINGSIDE_CASTLING,
    QUEENSIDE_CASTLING
};

const int KSCASTLING_KING_X = 6;
const int KSCASTLING_ROOK_X = 5;

const int QSCASTLING_KING_X = 2;
const int QSCASTLING_ROOK_X = 3;

const Position WHITE_KING_POSITION = Position( 4, 7 );
const Position BLACK_KING_POSITION = Position( 4, 0 );

const Position WHITE_K_ROOK_POSITION = Position( 7, 7 );
const Position WHITE_Q_ROOK_POSITION = Position( 0, 7 );

const Position BLACK_K_ROOK_POSITION = Position( 7, 0 );
const Position BLACK_Q_ROOK_POSITION = Position( 0, 0 );

class PiecesManipulator
{
public:
    PiecesManipulator( Board* board = 0 );
    ~PiecesManipulator();

    bool undo( bool isSilent = false );
    bool redo();

    Error makeAMove( const Position& from, const Position& to , Colour colour );

    bool castling( const Colour& colour, const CastlingType& type );

    void flushUndo();
    void flushRedo();

    bool kingInCheck( const Colour& kingColour );

    void setUndoMoves( const QStack< Movement* >& movesStack );
    QStack< Movement* > undoMoves() const;

    void setRedoMoves( const QStack< Movement* >& movesStack );
    QStack< Movement* > redoMoves() const;

private:
    bool isCastlingAllowed( ChessPiece* const king, ChessPiece* const rook, const CastlingType& type );

private:
    QStack< Movement* > m_undoMoves;
    QStack< Movement* > m_redoMoves;
    Colour              m_currentColour;
    Board*              m_board;
};

}
}
}

#endif // PIECESMANIPULATOR_H
