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
    Widget( QWidget *parent = 0 );
    ~Widget();

    void setInterface( const BoardInterface& interface );
    BoardInterface interface() const;

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

signals:
    void clickCell(QPoint point);

private:
    MovesListView* m_listView;
    GameEngine*    m_engine;
    BoardInterface m_interface;
    QPoint m_point;
};

#endif // WIDGET_H
