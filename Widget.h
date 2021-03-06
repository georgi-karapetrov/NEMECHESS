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
#include "PiecesManipulator.h"
#include "BoardInterface.h"
#include "Board.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "King.h"
#include "Movement.h"
#include "SimpleMovement.h"
#include "ComplexMovement.h"
#include "MovesListModel.h"

using namespace Chess::GameLogic::GameComponents;
using namespace Chess::ChessComponents::ChessPieces;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget( QWidget* parent = 0 );
    ~Widget();

    void setMovesListModel( MovesListModel* model );

    void setInterface( const BoardInterface& interface );
    BoardInterface interface() const;

    void setView( QListView* view );
    QListView* view() const;

    void chichuAdi( QPainter& painter,
                    const int x = 0,
                    const int y = 0,
                    const int size = 5,
                    const int xOffset = 0,
                    const int yOffset = 0 );

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

signals:
    void clickCell( QPoint point );

public slots:
    void movesListItemClicked( QModelIndex );
    void figureSelectedListener( const Position& );

private:
    QListView*     m_view;
    BoardInterface m_interface;
};

#endif // WIDGET_H
