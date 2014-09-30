#ifndef GAMEENGINE_H
#define GAMEENGINE_H

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
    GameEngine( QWidget* parent           =  0,
                const int rows            =  8,
                const int columns         =  8,
                const int cellWidth       = 50,
                const int cellHeght       = 50,
                const int numberOfPlayers =  2,
                Colour startingColour     = white );

    GameEngine( Board* board, QObject* parent = 0 );
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

private:
    Position fromChessNotation( const char& x, const char& y );
    void setPiecesForStandardGame( const Colour& colour );

    void quit();
       /*seek and*/
    void destroy();

    void pressEnterToContinue();

    Position toPosition( QPoint point );
    void addMoveToList( Movement* move );
    QString toChessNotation( const Position& position );

public slots:
    void clickCellListener(const QPoint &point);

private:
    Board*            m_board;
    PiecesManipulator m_manipulator;
    vector< Player >  m_players;
    Colour            m_currentPlayerColour;
    bool              m_quit;
    Position          m_from;
    Position          m_to;
    bool              m_isFigureSelected;
    MovesListModel*   m_model;
    Widget*           m_widget;
};

}
}
}

#endif // GAMEENGINE_H
