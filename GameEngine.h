#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#define PLAYER1 m_players[ 0 ]
#define PLAYER2 m_players[ 1 ]

#include "Board.h"
#include "PiecesManipulator.h"
#include "Player.h"

#include <QObject>
#include <string>
#include <vector>
#include <QDebug>

#include "BoardInterface.h"
#include "Position.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "MovesListModel.h"
#include <Widget.h>

namespace Chess{
namespace ChessComponents {
namespace PlayField {
    class Board;

}
}

namespace GameLogic{
namespace GameComponents{

using std::cin;
using std::string;
using namespace Chess::ChessComponents::PlayField;

const int ROOK_OFFSET     = 0;
const int KNIGHT_OFFSET   = 1;
const int BISHOP_OFFSET   = 2;
const int QUEEN_OFFSET    = 3;
const int KING_OFFSET     = 4;
const int VERTICAL_OFFSET = 7;

enum Instruction
{
    Quit,
    Move,
    Undo,
    Redo,
    Pass,
    Castling,
    FastForward,
    Invalid
};

class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine( const int rows               =  8,
                const int columns            =  8,
                const int cellWidth          = 80,
                const int cellHeght          = 80,
                const int numberOfPlayers    =  2,
                Colour startingColour = Chess::white );

    virtual ~GameEngine();

    void setBoard( Board* const board );
    Board* board() const;

    void setManipulator( const PiecesManipulator& manipulator );
    PiecesManipulator manipulator() const;

    void setModel( MovesListModel* model );
    MovesListModel* model();

    void addPlayer( Player& player );
    void nextPlayersTurn();

    void parseInstructions( const string& instruction );
    static Instruction instructionFromCode( const char& ch );

    void run();
    void setStandardGame();
    void chewCoordinates( const QPoint& point );

    QString toChessNotation( const Position& position );

private:
    Position fromChessNotation( const char& x, const char& y );
    void setPiecesForStandardGame( const Colour& colour );
    void setPiecesForTesting();

    void quit();
       /*seek and*/
    void destroy();

    void pressEnterToContinue();

    Position toPosition( QPoint point );
    void addMoveToList( Movement* move );
    void selectFigure( const Position& position );

    bool kingIsSafe( const Position& from, const Position& to, const Colour& colour );

signals:
    void jobFinished();
    void figureSelected( const Position& position );

public slots:
    void clickCellListener( const QPoint& point );
    void lastMoveClickedListener( const QModelIndex& index );

private:
    Board*            m_board;
    PiecesManipulator m_manipulator;
    vector< Player >  m_players;
    Colour            m_currentPlayerColour;
    bool              m_quit;
    Position          m_from;
    Position          m_to;
    bool              m_isFigureSelected;
    bool              m_isFirstClick;
    bool              m_inCheckFlag;
    MovesListModel*   m_model;
    Widget*           m_widget;
};

}
}
}

#endif // GAMEENGINE_H
