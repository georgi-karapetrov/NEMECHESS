#include "MovesListModel.h"

MovesListModel::MovesListModel( QObject* parent )
    : QAbstractListModel( parent ),
      m_lastRowClicked( this->rowCount() )
{
}

int MovesListModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent );
    return 1;
}

int MovesListModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent );
    return m_list.size();
}

bool MovesListModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
//    qDebug() << "setData()";
    if ( index.isValid() && role == Qt::EditRole )
    {
        m_list.insert( index.row(), value.toString() );

        emit ( dataChanged( index, index ) );
        return true;
    }
    return false;
}

QVariant MovesListModel::data( const QModelIndex& index, int role ) const
{
//    qDebug() << "data()";
    if ( !index.isValid() )
    {
        return QVariant();
    }

    switch( role )
    {
    case Qt::TextAlignmentRole:
        return QVariant( Qt::AlignLeft | Qt::AlignVCenter );

    case Qt::EditRole:
    case Qt::DisplayRole:
        return m_list.at( index.row() );

    case Qt::TextColorRole:
        if ( m_lastRowClicked < index.row() )
        {
            return QColor( Qt::gray );
        }
        return QColor( Qt::black );

    default:
        return QVariant();
    }

    return QVariant();
}

//QString MovesListModel::toChessNotation( const Position& position )
//{
//    return QString( 'a' + position.x() + QString::number( m_board->rows() - position.y() ) );
//}

void MovesListModel::addMove( const QString& move )
{
    QModelIndex index = createIndex( 0, 0 );
//    QString move( toChessNotation( from ) + " -> " + toChessNotation( to ) );
    m_list << move;

    emit( dataChanged( index, index ) );
}

Qt::ItemFlags MovesListModel::flags( const QModelIndex& index ) const
{
    if ( ! index.isValid() )
    {
        return QAbstractListModel::flags( index );
    }

    return QAbstractListModel::flags( index ) | Qt::ItemIsEditable;
}

void MovesListModel::setLastRowClicked( const int& row )
{
    m_lastRowClicked = row;
    emit dataChanged( this->index( m_lastRowClicked, 0 ),
                      this->index( this->rowCount() > 0 ? this->rowCount() - 1 : 0, this->columnCount() - 1 ) );
}

int MovesListModel::lastRowClicked() const
{
    return m_lastRowClicked;
}

void MovesListModel::clearRedoMoves()
{
    auto iter = m_list.begin();
    for ( int i = 0; i < m_lastRowClicked; ++ i )
    {
        ++ iter;
    }
    m_list.erase( iter, m_list.end() );
}
