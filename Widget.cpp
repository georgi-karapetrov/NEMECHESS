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
    m_listView = new MovesListView( &m_manipulator, this );
    m_listView->setGeometry( BoardInterface::X_OFFSET * 3 + m_board->columns() * m_board->cellWidth(),
                             BoardInterface::Y_OFFSET,
                             200,
                             m_board->rows() * m_board->cellHeight());

    m_listView->setEditTriggers( QAbstractItemView::NoEditTriggers );
//    m_listModel = new QStandardItemModel( m_listView );
//    QStandardItem* item = new QStandardItem( QString( "med" ) );
//    m_listModel->appendRow( item );
//    m_listView->setModel( m_listModel );

//    connect( m_btnClose, SIGNAL(clicked()), this, SLOT(btnCloseClick()) );
//    connect( m_listView, SIGNAL(clicked()), this, SLOT(listItemClicked(m_listView->currentIndex())) );
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

    if ( m_manipulator.kingInCheck( Chess::white ) )
    {
        qDebug() << "white king in check";
    }

    if ( m_manipulator.kingInCheck( Chess::black ) )
    {
        qDebug() << "black king in check";
    }

    if ( m_isFigureSelected )
    {
        qDebug() << "First condition";
        m_to = position;
        if ( m_manipulator.makeAMove( m_from, m_to, m_board->pieceAt( m_from )->colour() ) == Success )
        {
            m_listView->addMove( this->toChessNotation( m_from ) + " -> " + this->toChessNotation( m_to ) );
        }

        m_from = Position( -1, -1 );
        m_to =   Position( -1, -1 );
        m_isFigureSelected = false;
    }
    else
    {
        qDebug() << "Second condition";
        if ( m_board->pieceAt( position ) )
        {
            qDebug() << "Third condition";
            m_from = position;
            /*
            for ( auto iter = m_board->pieceAt( m_from )->allowedMovements().begin(); iter != m_board->pieceAt( m_from )->allowedMovements().end(); ++ iter )
            {
                qDebug() << ( *iter ).x() << ( *iter ).y();
            }
            */
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

QString Widget::toChessNotation( const Position& position )
{
    return QString( 'a' + position.x() + QString::number( m_board->rows() - position.y() ) );
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
