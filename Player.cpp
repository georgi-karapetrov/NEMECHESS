#include "Player.h"
#include "ChessPiece.h"
#include "Board.h"

using namespace Chess;
using namespace Chess::GameLogic::GameComponents;

Player::Player( Board* const board, const Colour& playsWith )
    : m_colour( playsWith ),
      m_board( board )
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
    const vector< ChessPiece* >& tempPieces  = m_colour == white ? m_board->whitePieces() : m_board->blackPieces();
    const vector< ChessPiece* >& enemyPieces = m_colour == white ? m_board->blackPieces() : m_board->whitePieces();

    bool inCheck = false;
    for ( auto iter = tempPieces.begin(); iter != tempPieces.end(); ++ iter )
    {
        if ( ( *iter )->pieceType() == KING_TYPE )
        {
            ChessPiece* falseKing = *iter;
            inCheck = m_board->inLoS( falseKing->position(), enemyPieces );
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

