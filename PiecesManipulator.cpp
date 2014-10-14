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
    //  m_capturedPieces( QStack< ChessPiece*  >() )
{
}

PiecesManipulator::~PiecesManipulator()
{
    cout << "~PiecesManipulator()\n";
    this->flushUndo();
}

Error PiecesManipulator::makeAMove( const Position& from, const Position& to, Colour colour )  // just do it
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

    if ( m_board->isPiece( to ) )
    {
        if ( m_board->pieceAt( from )->pieceType()  == KING_TYPE
             && m_board->pieceAt( to )->pieceType() == ROOK_TYPE
             && m_board->pieceAt( from )->colour()  == m_board->pieceAt( to )->colour() )
        {
            CastlingType castlingType = m_board->pieceAt( from )->position().x() < m_board->pieceAt( to )->position().x() ? KINGSIDE_CASTLING
                                                                                                                          : QUEENSIDE_CASTLING;
           if ( this->castling( m_board->pieceAt( from )->colour(), castlingType ) )
           {
               return Castling;
           }
        }
    }

//    if ( this->kingInCheck( colour ) )// && m_board->pieceAt( from )->pieceType() != KING_TYPE )
//    {
//        qDebug() << "Your king's in trouble!";
//        return Check;
//    }

    //if the figure attempts m_capturedPiecesto move in its allowed movements
    vector< Position > tmp = m_board->pieceAt( from )->allowedMovements();
    if ( std::find( tmp.begin(), tmp.end(), to ) == tmp.end() )
    {
        return InvalidDestination;
    }

    Movement* movement = new SimpleMovement( from, to, m_board );

//    if ( ! movement->doMovem_capturedPieces() )
//    {
//        return InvalidDestination;
//    }

    ChessPiece* forCapture = 0;

    if ( m_board->isPiece( to ) && ! m_board->isAlly( to, m_board->pieceAt( from )->colour() ) )
    {
        forCapture = m_board->pieceAt( to );
    }

    if ( movement->doMove() )
    {
        if ( forCapture != 0 )
        {
            movement->setFlags( CAPTURE_FLAG );
            m_capturedPieces.push( forCapture );
        }
        m_undoMoves->push( movement );
        return Success;
    }

    return InvalidDestination;

}

QStack< ChessPiece* > PiecesManipulator::capturedPieces() const
{
    return m_capturedPieces;
}

bool PiecesManipulator::undo( bool isSilent )
{
    if ( ! m_undoMoves->empty() )
    {
        Movement* const topMovement = m_undoMoves->pop();

        topMovement->undoMove();

        if ( ! m_capturedPieces.empty() && topMovement->flags().testFlag( CAPTURE_FLAG  ) )
        {
            m_board->addPiece( m_capturedPieces.pop() );
        }

        if ( ! isSilent )
        {
            m_redoMoves->push( topMovement );
        }
        qDebug() << "A hush falls on the battlefield";
        return true;
    }

    return false;
}

void PiecesManipulator::flushUndo()
{
    cout << "PiecesManipulator::destroy()\n";
    while ( ! m_undoMoves->empty() )
    {
//        delete m_undoMoves->top();
        m_undoMoves->pop();
    }
}


bool PiecesManipulator::redo()
{
    if ( !m_redoMoves->empty() )
    {
        m_redoMoves->top()->doMove();
        m_undoMoves->push( m_redoMoves->top() );
        m_redoMoves->pop();
        return true;
    }
    return false;
}

void PiecesManipulator::flushRedo()
{
    while ( !m_redoMoves->empty() )
    {
//        delete m_redoMoves->top();
        m_redoMoves->pop();
    }
}

bool PiecesManipulator::castling( const Colour& colour, const CastlingType& type )
{
    int castlingOffsetKing = 0;
    int castlingOffsetRook = 0;

    Position kingPosition = colour == Chess::white ? WHITE_KING_POSITION : BLACK_KING_POSITION;

    ChessPiece* king = m_board->pieceAt( kingPosition );

    Position rookPosition = colour == Chess::white ? type == KINGSIDE_CASTLING ? WHITE_K_ROOK_POSITION : WHITE_Q_ROOK_POSITION
                                                   : type == KINGSIDE_CASTLING ? BLACK_K_ROOK_POSITION : BLACK_Q_ROOK_POSITION;
    ChessPiece* rook = m_board->pieceAt( rookPosition );

    if ( ! m_board->isPiece( kingPosition )
         || ! m_board->isPiece( rookPosition ) )
    {
        return false;
    }

    if ( king->pieceType() != KING_TYPE || rook->pieceType() != ROOK_TYPE )
    {
        return false;
    }

    if ( ! this->isCastlingAllowed( king, rook, type ) )
    {
        return false;
    }


    if ( type == KINGSIDE_CASTLING )
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
                                                           king->position().y() ),
                                                 m_board );
    Movement* rookMovement = new SimpleMovement( rook->position(),
                                                 Position( castlingOffsetRook,
                                                           rook->position().y() ),
                                                 m_board );
    vector < Movement* > simpleMovements;

    simpleMovements.push_back( rookMovement );
    simpleMovements.push_back( kingMovement );

    m_board->movePiece( king->position(), Position( castlingOffsetKing, king->position().y() ) );
    m_board->movePiece( rook->position(), Position( castlingOffsetRook, rook->position().y() ) );

    MovementFlags castlingFlag = type == KINGSIDE_CASTLING ? KINGSIDECASTLING_FLAG : QUEENSIDECASTLING_FLAG;
    Movement* castlingMovement = new ComplexMovement( m_board, simpleMovements, castlingFlag  );

    m_undoMoves->push( castlingMovement );

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

    if ( type == KINGSIDE_CASTLING )
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
    else // if type == QUEENSIDE_CASTLING
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

void PiecesManipulator::setUndoMoves( QStack< Movement* >* movesStack )
{
    m_undoMoves = movesStack;
}

QStack< Movement* >* PiecesManipulator::undoMoves() const
{
    return m_undoMoves;
}

void PiecesManipulator::setRedoMoves( QStack<Movement *>* movesStack )
{
    m_redoMoves = movesStack;
}

QStack< Movement* >* PiecesManipulator::redoMoves() const
{
    return m_redoMoves;
}

