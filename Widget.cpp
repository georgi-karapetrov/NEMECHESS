#include "Widget.h"

Widget::Widget( QWidget* parent )
    : QWidget( parent ),
      m_point( QPoint( -1, -1 ) )
{
    qDebug() << "Widget()";
}

Widget::~Widget()
{
}

void Widget::setInterface( const BoardInterface& interface )
{
    m_interface = interface;
}

BoardInterface Widget::interface() const
{
    return m_interface;
}

void Widget::setView( QListView* view )
{
    m_view = view;
}

QListView* Widget::view()
{
    return m_view;
}

void Widget::paintEvent( QPaintEvent* event )
{
    QWidget::paintEvent( event );

    QPainter painter( this );
    painter.setPen( Qt::black );
    painter.setBrush( Qt::NoBrush );
    m_interface.drawBoard( painter );
}

void Widget::mouseReleaseEvent( QMouseEvent* event )
{
    Q_UNUSED( event );

    m_point = this->mapFromGlobal( ( QCursor::pos() ) );

    emit clickCell( m_point );

    this->repaint(); //remove!
}

