#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H

#include <QBitmap>
#include <QColor>
#include <QImage>
#include <QLabel>
#include <QPainter>
//#include <QWidget>
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
    BoardInterface( Board* board = 0, QWidget* parent = 0 );

    void drawBoard( QPainter& painter );

private:
    QColor alternateColour( const QColor& colour );
    void drawPosition( QPainter& painter, const Position& position, const QColor& colour );
    void drawNotationRulers( QPainter& painter );
public:
    void drawChessPiece( QPainter& painter, ChessPiece* chessPiece = 0 );

private:
    Board*   m_board;
    QWidget* m_parent;
};

#endif // BOARDINTERFACE_H
