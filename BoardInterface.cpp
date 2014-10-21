#include "BoardInterface.h"

const int BoardInterface::X_OFFSET = 20;
const int BoardInterface::Y_OFFSET = 20;
const QString BoardInterface::IMG_FOLDER = "impr/"; // other is "etc/"
const QString BoardInterface::EXT = ".png";

BoardInterface::BoardInterface( Board* board )
    : m_board( board ),
      m_selectedPosition( -1, -1 )
{
}

BoardInterface& BoardInterface::operator=( const BoardInterface& other )
{
    m_board = other.m_board;
    m_parent = other.m_parent;
    return *this;
}

QColor BoardInterface::alternateColour( const QColor& colour )
{
    if ( colour == Qt::white )
    {
        return Qt::gray;
    }

    return Qt::white;
}

void BoardInterface::drawPosition( QPainter& painter, const Position& position, const QColor& colour, bool bordered )
{
    QRect rect( position.x(),
                position.y(),
                m_board->cellWidth(),
                m_board->cellHeight() );

    painter.fillRect( rect, colour );

    if ( bordered )
    {
        painter.drawRect( rect );
    }

}

void BoardInterface::drawBoard( QPainter& painter )
{
    this->drawNotationRulers( painter );

    for ( int i = 0; i < m_board->columns(); ++ i )
    {
        QColor currentColour = i % 2 == 0 ? Qt::white
                                          : Qt::gray;
        for ( int j = 0; j < m_board->rows(); ++ j )
        {
            this->drawPosition( painter,
                                Position( X_OFFSET + i * m_board->cellWidth(),
                                          Y_OFFSET + j * m_board->cellHeight() ),
                                currentColour );
            currentColour = this->alternateColour( currentColour );
        }
    }

    if ( m_selectedPosition != Position( -1, -1 ) )
    {
        this->drawPosition( painter,
                            Position( X_OFFSET + m_selectedPosition.x() * m_board->cellWidth(),
                                      Y_OFFSET + m_selectedPosition.y() * m_board->cellHeight() ),
                            QColor( Qt::magenta ) );

        // paranoid nullptr check
        if ( m_board->isPiece( m_selectedPosition ) )
        {
            this->markAllowedMovements( painter, m_board->pieceAt( m_selectedPosition ) );
        }
        m_selectedPosition = Position( -1, -1 );
//        qDebug() << "Selected position:" << m_selectedPosition.x() << m_selectedPosition.y();
    }

    //some lines that should be there but are not
    painter.drawLine( X_OFFSET, Y_OFFSET, X_OFFSET, m_board->rows() * m_board->cellHeight() + Y_OFFSET );
    painter.drawLine( X_OFFSET, Y_OFFSET, m_board->columns() * m_board->cellWidth() + X_OFFSET, Y_OFFSET );

    for ( int i = 0; i < m_board->rows(); ++ i )
    {
        for ( int j = 0; j < m_board->columns(); ++ j )
        {
            unordered_map< Position, ChessPiece* >::const_iterator iter = m_board->piecesMap().find( Position( i, j ) );
            if ( iter->second != 0 )
            {
                this->drawChessPiece( painter, iter->second );
            }
        }
    }
}

void BoardInterface::drawNotationRulers( QPainter& painter  )
{

    //numbers column
    for ( int i = 0; i < m_board->rows(); ++ i )
    {
        painter.drawText( X_OFFSET / 4, Y_OFFSET + 2 + i *  m_board->cellHeight() +  m_board->cellHeight() / 2, QString(  m_board->rows() + '0' - i ) );
        painter.drawText( X_OFFSET +  m_board->columns() *  m_board->cellWidth() + X_OFFSET / 4, Y_OFFSET + i *   m_board->cellHeight() +  m_board->cellHeight() / 2, QString(  m_board->rows() + '0' - i ) );
    }

    //letter rows
    for ( int i = 0; i <  m_board->columns(); ++ i )
    {
        painter.drawText( X_OFFSET + i *  m_board->cellWidth() +  m_board->cellWidth() / 2, Y_OFFSET / 2 + 2, QString( 'a' + i ) );
        painter.drawText( X_OFFSET + i *  m_board->cellWidth() +  m_board->cellWidth() / 2, Y_OFFSET * 2 +  m_board->rows() *  m_board->cellHeight(), QString( 'a' + i ) );
    }
}

void BoardInterface::drawChessPiece( QPainter& painter, ChessPiece* chessPiece )
{
    QImage image;
    image.load( IMG_FOLDER + QString::number( chessPiece->colour() ) + "/" + QString::number( chessPiece->pieceType() ) + EXT );

    const QPixmap tmpPixmap = QPixmap::fromImage( image );


    int scaleFactor = image.width() > image.height() ? image.width() / m_board->cellWidth()
                                                     : image.height() / m_board->cellHeight();

    painter.drawPixmap( BoardInterface::X_OFFSET + 2 + chessPiece->position().x() * m_board->cellWidth(),
                        BoardInterface::Y_OFFSET + 2 + chessPiece->position().y() * m_board->cellHeight(),
                        image.width() / ( scaleFactor + 1 ), // to look cooler
                        image.height() / ( scaleFactor + 1 ),
                        tmpPixmap );
}

void BoardInterface::setSelectedPosition( const Position& position )
{
    m_selectedPosition = position;
}

Position BoardInterface::selectedPosition() const
{
    return m_selectedPosition;
}

void BoardInterface::markAllowedMovements( QPainter& painter, ChessPiece* chessPiece )
{

    QVector< Position > helper = chessPiece->allowedMovements();
    for ( auto iter = helper.begin(); iter != helper.end(); ++ iter )
    {
        int x = ( *iter ).x();
        int y = ( *iter ).y();

        if ( m_board->isValidPosition( *iter ) )
        this->drawPosition( painter,
                            Position( X_OFFSET + x * m_board->cellWidth(),
                                      Y_OFFSET + y * m_board->cellHeight() ),
                            QColor( Qt::yellow ) );
    }
}
