#include "Widget.h"



Widget::Widget( Board* board, QWidget* parent )
    : m_board( board ),
      m_boardInterface( board, this ),
      QWidget( parent )
{
}

Widget::~Widget()
{
}

void Widget::paintEvent( QPaintEvent* event )
{
    QWidget::paintEvent( event );

    QPainter painter( this );
    painter.setPen( Qt::black );
    painter.setBrush( Qt::NoBrush );
    m_boardInterface.drawBoard( painter );
//    m_boardInterface.drawChessPiece( pawn );
}

void Widget::mouseReleaseEvent( QMouseEvent* event )
{
    Q_UNUSED( event );
    QPoint point = this->mapFromGlobal( ( QCursor::pos() ) );
    qDebug() << toPosition( point.x(), point.y() ).x() << toPosition( point.x(), point.y() ).y();
}

Position Widget::toPosition( const int x, const int y )
{
    return Position( floor( ( x - BoardInterface::X_OFFSET ) / 50 ), floor ( ( y - BoardInterface::Y_OFFSET ) / 50 ) );
}
