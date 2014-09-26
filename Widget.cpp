#include "Widget.h"



Widget::Widget( Board* board, QWidget* parent )
    : QWidget( parent ),
      m_board( board ),
      m_boardInterface( board, this ),
      m_manipulator( board ),
      m_isFigureSelected( false ),
      m_from( Position( -1, -1 ) ),
      m_to  ( Position( -1, -1 ) )
{
}

Widget::~Widget()
{
}

void Widget::setBoard( Board* board )
{
    m_board = board;
}

Board* Widget::board() const
{
    return m_board;
}

void Widget::paintEvent( QPaintEvent* event )
{
    QWidget::paintEvent( event );

    QPainter painter( this );
    painter.setPen( Qt::black );
    painter.setBrush( Qt::NoBrush );
    m_boardInterface.drawBoard( painter );
}

void Widget::mouseReleaseEvent( QMouseEvent* event )
{
    Q_UNUSED( event );

    QPoint point = this->mapFromGlobal( ( QCursor::pos() ) );
    Position position = toPosition( point );

    if ( m_isFigureSelected )
    {
        m_to = position;
        qDebug() << m_manipulator.makeAMove( m_from, m_to, m_board->pieceAt( m_from )->colour() );
        m_from = Position( -1, -1 );
        m_to = Position( -1, -1 );
        m_isFigureSelected = false;
    }
    else
    {
        if ( m_board->pieceAt( position ) )
        {
            m_from = position;
            m_isFigureSelected = true;
        }
    }

    repaint();
}

Position Widget::toPosition( QPoint point )
{
    return Position( floor( ( point.x() - BoardInterface::X_OFFSET ) / m_board->cellWidth() ),
                     floor( ( point.y() - BoardInterface::Y_OFFSET ) / m_board->cellHeight() ) );
}

/*
void Widget::mouseReleaseEvent( QMouseEvent* event )
{
    Q_UNUSED( event );

    QPoint point = this->mapFromGlobal( ( QCursor::pos() ) );
    Position position = toPosition( point );

    if ( !m_board->isPiece( position ) && !m_isFigureSelected )
    {
        qDebug() << "Empty cell";
    }
    else
    {
        if ( m_board->isPiece( position ) && !m_isFigureSelected )
        {
            m_from = position;
            m_isFigureSelected = true;
        }
        else if ( m_from == position  )
        {
            m_from = Position( -1, -1 );
            m_isFigureSelected = false;
        }

        QString currColour = "Null";
        if ( m_board->isValidPosition( m_from ) ) //if a figure is selected
        {
            currColour =  m_board->pieceAt( m_from )->colour() == Chess::white ? "white" : "black";
            qDebug() << "Error code:" << m_manipulator.makeAMove( m_from, position, m_board->pieceAt( m_from )->colour() );
            m_isFigureSelected = false;
        }


        qDebug() << "m_from" << m_from.x() << m_from.y();
        qDebug() << "position" << position.x() << position.y();
        qDebug() << currColour;
    }
    repaint();
}
*/
