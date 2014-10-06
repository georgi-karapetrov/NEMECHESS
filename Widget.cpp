#include "Widget.h"

Widget::Widget( QWidget* parent )
    : QWidget( parent )
{
    qDebug() << "Widget()";
    m_view = new QListView( this );

    connect(m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(movesListItemClicked(QModelIndex)));
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

QListView* Widget::view() const
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

    QPoint point = this->mapFromGlobal( ( QCursor::pos() ) );

    emit clickCell( point );
}

void Widget::setMovesListModel( MovesListModel* model )
{
    m_view->setModel( model );
}

void Widget::movesListItemClicked(QModelIndex index)
{
    qDebug() << index.row();
}

void Widget::figureSelectedListener( const Position& position )
{
    m_interface.setSelectedPosition( position );
    this->repaint();
//    m_interface.setSelectedPosition( Position( -1, -1 ) );
}
