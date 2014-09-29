#ifndef WIDGET_H
#define WIDGET_H

#include <cmath>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>

#include "Position.h"
#include "GameEngine.h"
#include "PiecesManipulator.h"
#include "BoardInterface.h"
#include "Board.h"
#include "ChessPieceInterface.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "King.h"
#include "Movement.h"
#include "SimpleMovement.h"
#include "ComplexMovement.h"
#include "MovesListView.h"

using namespace Chess::GameLogic::GameComponents;
using namespace Chess::ChessComponents::ChessPieces;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget( Board* board = 0, QWidget *parent = 0 );
    ~Widget();

    void setBoard( Board* board );
    Board* board() const;

private:
    Position toPosition( QPoint point );
    void addMoveToList( Movement* move );
    QString toChessNotation( const Position& position );

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

private slots:


private:
    BoardInterface      m_boardInterface;
    Board*              m_board;
    PiecesManipulator   m_manipulator;
    Position            m_from;
    Position            m_to;
    bool                m_isFigureSelected;
    MovesListView*      m_listView;
};

#endif // WIDGET_H
