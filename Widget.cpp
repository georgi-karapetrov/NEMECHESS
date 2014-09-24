#include "Widget.h"

Widget::Widget( Board* board, QWidget* parent )
    : m_board( board ),
      m_boardInterface( board ),
      QWidget( parent )
{
    ChessPiece* pawn = new King( Position( 1, 1 ), Chess::white, board );
    ChessPieceInterface cpi( pawn, board, this );
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

}
