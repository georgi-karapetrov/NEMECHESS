#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H

#include <QBitmap>
#include <QColor>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QPushButton>

#include "Board.h"
#include "Position.h"

class QWidget;

using namespace Chess::ChessComponents::PlayField;

class BoardInterface
{

public:
    static const int X_OFFSET;
    static const int Y_OFFSET;
    static const QString IMG_FOLDER;
    static const QString EXT;

public:
    BoardInterface( Board* board = 0 );

    void drawBoard( QPainter& painter );
    void drawChessPiece( QPainter& painter, ChessPiece* chessPiece = 0 );

    BoardInterface& operator=( const BoardInterface& other );

    void setSelectedPosition( const Position& position );
    Position selectedPosition() const;

private:
    QColor alternateColour( const QColor& colour );
    void drawPosition( QPainter& painter, const Position& position, const QColor& colour, bool bordered = true );
    void drawNotationRulers( QPainter& painter );

    void markAllowedMovements( QPainter& painter, ChessPiece* chessPiece );

private:
    Board*   m_board;
    QWidget* m_parent;
    Position m_selectedPosition;
};

#endif // BOARDINTERFACE_H
