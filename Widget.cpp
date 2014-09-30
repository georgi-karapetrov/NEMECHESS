#include "Widget.h"

Widget::Widget( QWidget* parent )
    : QWidget( parent ),
      m_point( QPoint( -1, -1 ) ),
      m_engine( new GameEngine( parent ) ),
      m_interface( m_engine->board(), this )

{
    qDebug() << "Widget()";

    connect( this, SIGNAL(clickCell(QPoint)), m_engine, SLOT(run(QPoint)));
    m_engine->setStandardGame();

//    m_listView = new MovesListView( m_engine->manipulator(), this );
//    m_listView->setGeometry( BoardInterface::X_OFFSET * 3 + m_engine->board()->columns() * m_engine->board()->cellWidth(),
//                             BoardInterface::Y_OFFSET,
//                             200,
//                             m_engine->board()->rows() * m_engine->board()->cellHeight());

//    m_listView->setEditTriggers( QAbstractItemView::NoEditTriggers );
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
//    m_engine.chewCoordinates( point );

    emit clickCell( m_point );

    this->repaint();
}

