#include "Player.h"
#include "ChessPiece.h"
#include "Board.h"

#include <set>

using namespace Chess;
using namespace Chess::GameLogic::GameComponents;

Player::Player( Board* const board, const Colour& playsWith , PiecesManipulator* manipulator )
    : m_colour( playsWith ),
      m_board( board ),
      m_manipulator( manipulator )
{
}

void Player::setColour( const Colour& colour )
{
    m_colour = colour;
}

Colour Player::colour() const
{
    return m_colour;
}

void Player::setBoard( Board* const board )
{
    m_board = board;
}

Board* Player::board() const
{
    return m_board;
}

bool Player::playsWith( const Colour& colour )
{
    return m_colour == colour;
}


bool Player::isInCheck() const
{
    const QVector< ChessPiece* > currentPlayerPieces  = m_colour == white ? m_board->whitePieces() : m_board->blackPieces();
    const QVector< ChessPiece* > allEnemyPieces = m_colour == white ? m_board->blackPieces() : m_board->whitePieces();

    // LIFE IS PAIN, House M.D.

    QSet< ChessPiece* > filteredEnemyPiecesSet;
    QSet< ChessPiece* > allEnemyPiecesSet = QSet< ChessPiece* >::fromList( allEnemyPieces.toList() );
    auto captured =  m_manipulator->capturedPieces();

    if ( captured.isEmpty() )
    {
        filteredEnemyPiecesSet = allEnemyPiecesSet;
    }
    else
    {
        QSet< ChessPiece* > capturedEnemyPiecesSet = QSet< ChessPiece* >::fromList( captured.toList() );
        filteredEnemyPiecesSet = allEnemyPiecesSet - capturedEnemyPiecesSet;
    }

//    const QVector< ChessPiece* > filteredEnemyPieces = std::set< ChessPiece* > );

    bool inCheck = false;
    for ( auto iter = currentPlayerPieces.begin(); iter != currentPlayerPieces.end(); ++ iter )
    {
        if ( ( *iter )->pieceType() == KING_TYPE )
        {
            ChessPiece* falseKing = *iter;
            inCheck = m_board->inLoS( falseKing->position(), QVector< ChessPiece* >::fromList( filteredEnemyPiecesSet.toList() ) );
            break;
        }
    }

    return inCheck;
}

void Player::setManipulator( PiecesManipulator* manipulator )
{
    m_manipulator = manipulator;
}

PiecesManipulator* Player::manipulator() const
{
    return m_manipulator;
}

bool Player::checkStatus()
{
    return m_manipulator->kingInCheck( m_colour );
}

