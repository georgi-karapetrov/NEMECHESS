#include "ChessPieceInterface.h"

const QString ChessPieceInterface::IMG_FOLDER = "etc/squares/";
const QString ChessPieceInterface::EXT = ".png";

ChessPieceInterface::ChessPieceInterface( ChessPiece* chessPiece, Board* board, QWidget* parent )
    : m_chessPiece( chessPiece ),
      m_board( board ),
      m_container( new QLabel( parent ) )
{
    m_image.load( IMG_FOLDER + QString::number( chessPiece->pieceType() ) + EXT );

    m_container->setScaledContents( true );

    int scaleFactor = m_image.width() > m_image.height() ? m_image.width() / m_board->cellWidth()
                                                         : m_image.height() / m_board->cellHeight();

    m_container->setGeometry( BoardInterface::X_OFFSET + 2 + chessPiece->position().x() * m_board->cellWidth(),
                              BoardInterface::Y_OFFSET + 2 + chessPiece->position().y() * m_board->cellHeight(),
                               m_image.width() / ( scaleFactor + 1 ),
                               m_image.height() / ( scaleFactor + 1 ) );

    m_container->setPixmap( QPixmap::fromImage( m_image ) );
}

ChessPieceInterface::~ChessPieceInterface()
{
}

int ChessPieceInterface::width() const
{
    return m_container->width();
}

int ChessPieceInterface::height() const
{
    return m_container->height();
}

void ChessPieceInterface::setChessPiece( ChessPiece* chessPiece )
{
    m_chessPiece = chessPiece;
}

ChessPiece* ChessPieceInterface::chessPiece() const
{
    return m_chessPiece;
}

void ChessPieceInterface::setImage( const QImage& image )
{
    m_image = image;
}

QImage ChessPieceInterface::image() const
{
    return m_image;
}

