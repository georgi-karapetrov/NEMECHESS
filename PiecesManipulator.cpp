#include "PiecesManipulator.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

using namespace Chess::GameLogic::GameComponents;

PiecesManipulator::PiecesManipulator( Board* board )
    : m_board( board )
{
}

PiecesManipulator::~PiecesManipulator()
{
    cout << "~PiecesManipulator()\n";
    this->flushUndo();
}

Error PiecesManipulator::makeAMove( const Position& from, const Position& to, Colour colour )
{
    if ( !m_board->isPiece( from ) || !m_board->isValidPosition( to ) )
    {
        return EmptyPosition;
    }

    if ( m_board->pieceAt( from )->colour() != colour )
    {
        return WrongColour;
    }

    if ( m_board->isPiece( to )
         && m_board->pieceAt( to )->pieceType() == KING_TYPE )
    {
        return KingCapture;
    }

//    if ( this->kingInCheck( colour ) )// && m_board->pieceAt( from )->pieceType() != KING_TYPE )
//    {
//        qDebug() << "Your king's in trouble!";
//        return Check;
//    }

    //if the figure attempts to move in its allowed movements
    vector< Position > tmp = m_board->pieceAt( from )->allowedMovements();
    if ( std::find( tmp.begin(), tmp.end(), to ) == tmp.end() )
    {
        return InvalidDestination;
    }

    Movement* movement = new SimpleMovement( from, to, m_board );

    if ( ! movement->doMove() )
    {
        return InvalidDestination;
    }

    m_undoMoves.push( movement );
    return Success;
}

void PiecesManipulator::undo( bool isSilent )
{
    if ( !m_undoMoves.empty() )
    {
        m_undoMoves.top()->undoMove();
        if ( ! isSilent )
        {
            m_redoMoves.push( m_undoMoves.top() );
            m_undoMoves.pop();
        }
    }
}

void PiecesManipulator::flushUndo()
{
    cout << "PiecesManipulator::destroy()\n";
    while ( ! m_undoMoves.empty() )
    {
        delete m_undoMoves.top();
        m_undoMoves.pop();
    }
}


void PiecesManipulator::redo()
{
    if ( !m_redoMoves.empty() )
    {
        m_redoMoves.top()->doMove();
        m_undoMoves.push( m_redoMoves.top() );
        m_redoMoves.pop();
    }
}

void PiecesManipulator::flushRedo()
{
    while ( !m_redoMoves.empty() )
    {
//        delete m_redoMoves.top();
        m_redoMoves.pop();
    }
}

bool PiecesManipulator::castling( const Colour& colour, const CastlingType& type )
{
    int castlingOffsetKing = 0;
    int castlingOffsetRook = 0;

    ChessPiece* king = colour == white ? m_board->pieceAt( WHITE_KING_POSITION ) : m_board->pieceAt( BLACK_KING_POSITION );

    Position rookPosition = colour == white ? type == Kingside ? WHITE_K_ROOK_POSITION : WHITE_Q_ROOK_POSITION
                                            : type == Kingside ? BLACK_K_ROOK_POSITION : BLACK_Q_ROOK_POSITION;
    ChessPiece* rook = m_board->pieceAt( rookPosition );

    if ( !m_board->isPiece( WHITE_KING_POSITION )
         || !m_board->isPiece( rookPosition ) )
    {
        return false;
    }

    if ( king->pieceType() != KING_TYPE || rook->pieceType() != ROOK_TYPE )
    {
        return false;
    }

    if ( ! isCastlingAllowed( king, rook, type ) )
    {
        return false;
    }


    if ( type == Kingside )
    {
        castlingOffsetKing = KSCASTLING_KING_X;
        castlingOffsetRook = KSCASTLING_ROOK_X;
    }
    else
    {
        castlingOffsetKing = QSCASTLING_KING_X;
        castlingOffsetRook = QSCASTLING_ROOK_X;
    }


    //faking movements here
    //resulting in crashing undo
    Movement* kingMovement = new SimpleMovement( king->position(),
                                                 Position( castlingOffsetKing,
                                                           king->position().y() ), m_board );
    Movement* rookMovement = new SimpleMovement( rook->position(),
                                                 Position( castlingOffsetRook,
                                                           rook->position().y() ), m_board );
    vector < Movement* > simpleMovements;

    simpleMovements.push_back( rookMovement );
    simpleMovements.push_back( kingMovement );

    m_board->movePiece( king->position(), Position( castlingOffsetKing, king->position().y() ) );
    m_board->movePiece( rook->position(), Position( castlingOffsetRook, rook->position().y() ) );


    Movement* castlingMovement = new ComplexMovement( m_board, simpleMovements );

    m_undoMoves.push( castlingMovement );

    return true;
}

bool PiecesManipulator::isCastlingAllowed( ChessPiece* const king, ChessPiece* const rook, const CastlingType& type )
{
    if ( m_board->passedMoves( king ) > 0
         || m_board->passedMoves( rook ) > 0 )
    {
        return false;
    }

    Colour colour = king->colour();
    const vector< ChessPiece* >& enemyPieces = colour == white ? m_board->blackPieces() : m_board->whitePieces();

    if ( type == Kingside )
    {
        for ( int i = king->position().x() + 1; i <= KSCASTLING_KING_X; ++ i )
        {
            Position position ( i, king->position().y() );
            bool obstacle = m_board->isAlly( position, colour );
            bool los = m_board->inLoS( position, enemyPieces );
            if ( obstacle || los )
            {
                return false;
            }
        }
    }
    else // if type == Queenside
    {
        for ( int i = king->position().x() - 1; i >= QSCASTLING_KING_X; -- i )
        {
            Position position ( i, king->position().y() );
            if ( m_board->isAlly( position, colour )
                 || m_board->inLoS( position, enemyPieces ) )
            {
                return false;
            }
        }
    }

    return true;
}

QString spitPieceType( ChessPiece* piece )
{
    if ( piece != 0 )
    {
        switch ( piece->pieceType() )
        {
        case PAWN_TYPE:
            return "PAWN";
        case ROOK_TYPE:
            return "ROOK";
        case BISHOP_TYPE:
            return "BISHOP";
        case KNIGHT_TYPE:
            return "KNIGHT";
        case QUEEN_TYPE:
            return "QUEEN";
        case KING_TYPE:
            return "KING";
        default:
            return "Something else";
        }
    }
    return "Something else";
}

bool PiecesManipulator::kingInCheck( const Colour& kingColour )
{
    const vector< ChessPiece* >& tempPieces  = kingColour == white ? m_board->whitePieces() : m_board->blackPieces();
    const vector< ChessPiece* >& enemyPieces = kingColour == white ? m_board->blackPieces() : m_board->whitePieces();

    bool inCheck = false;
    for ( auto iter = tempPieces.begin(); iter != tempPieces.end(); ++ iter )
    {
        if ( ( *iter )->pieceType() == KING_TYPE )
        {
            ChessPiece* falseKing = *iter;
//            qDebug() <<  "Das figure: " << spitPieceType(falseKing);
            inCheck = m_board->inLoS( falseKing->position(), enemyPieces );
            break;
        }
    }

    return inCheck;
}

void PiecesManipulator::setUndoMoves( const QStack< Movement* >& movesStack )
{
    m_undoMoves = movesStack;
}

QStack< Movement* > PiecesManipulator::undoMoves() const
{
    return m_undoMoves;
}

void PiecesManipulator::setRedoMoves( const QStack< Movement* >& movesStack )
{
    m_redoMoves = movesStack;
}

QStack< Movement* > PiecesManipulator::redoMoves() const
{
    return m_redoMoves;
}

