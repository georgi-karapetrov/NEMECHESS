#include "MovesListView.h"

MovesListView::MovesListView( PiecesManipulator* manipulator, QWidget* parent )
    : m_manipulator( manipulator ),
      QListView( parent ),
      m_parent( parent )
{
    m_listModel = new QStandardItemModel( this );
    this->setModel( m_listModel );



    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(listItemClicked(QModelIndex)));
}

void MovesListView::addMove( const QString& move )
{
    QStandardItem* item = new QStandardItem( move );
    m_listModel->appendRow( item );
}

void MovesListView::listItemClicked( QModelIndex index )
{
    for ( int i = index.row(); i < m_listModel->rowCount(); ++ i )
    {
        m_manipulator->undo();
        this->model()->setData( this->model()->index( i, 0 ), QBrush( Qt::gray ), Qt::ForegroundRole );
//        m_listModel->removeRow( index.row() );
    }
    m_parent->repaint();
}

void MovesListView::setManipulator( PiecesManipulator* manipulator )
{
    m_manipulator = manipulator;
}

PiecesManipulator* MovesListView::manipulator() const
{
    return m_manipulator;
}
