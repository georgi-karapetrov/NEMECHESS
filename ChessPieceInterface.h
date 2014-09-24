#ifndef CHESSPIECEINTERFACE_H
#define CHESSPIECEINTERFACE_H

#include <QDebug>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QString>

#include "Board.h"
#include "ChessPiece.h"
#include "Position.h"
#include "BoardInterface.h"

using namespace Chess::ChessComponents::ChessPieces;
using namespace Chess::ChessComponents::PlayField;

class ChessPieceInterface
{
    static const QString IMG_FOLDER;
    static const QString EXT;

public:
    ChessPieceInterface( ChessPiece* chessPiece = 0, Board* board = 0, QWidget* parent = 0 );
    ~ChessPieceInterface();

    int width() const;
    int height() const;

    void setChessPiece( ChessPiece* chessPiece );
    ChessPiece* chessPiece() const;

    void setImage( const QImage& image );
    QImage image() const;

private:
    QImage      m_image;
    QLabel*     m_container;
    ChessPiece* m_chessPiece;
    Board*      m_board;
};

#endif // CHESSPIECEINTERFACE_H
