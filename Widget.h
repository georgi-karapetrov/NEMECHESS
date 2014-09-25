#ifndef WIDGET_H
#define WIDGET_H

#include <cmath>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>

#include "Position.h"
#include "BoardInterface.h"
#include "Board.h"
#include "ChessPieceInterface.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "King.h"

using namespace Chess::ChessComponents::ChessPieces;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget( Board* board = 0, QWidget *parent = 0 );
    ~Widget();

private:
    Position toPosition( const int x, const int y );

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

private:
    Board*         m_board;
    BoardInterface m_boardInterface;
};

#endif // WIDGET_H
