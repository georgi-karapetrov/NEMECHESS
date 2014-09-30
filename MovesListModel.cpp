#include "MovesListModel.h"

MovesListModel::MovesListModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

int MovesListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent );
    return 1;
}

int MovesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent );
    return m_list.size();
}

bool MovesListModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if ( role == Qt::EditRole )
    {
        m_list.insert( index.row(), value.toString() );
        return true;
    }
    return false;
}

QVariant MovesListModel::data( const QModelIndex& index, int role ) const
{
    switch ( role )
    {
    case Qt::DisplayRole:
        return m_list.at( index.row() );

    case Qt::TextColorRole:
        return QColor( Qt::gray );

    default:
        return QVariant();
    }

    return QVariant();
}

void MovesListModel::addMove( const QString& move )
{
    m_list << move;
}

