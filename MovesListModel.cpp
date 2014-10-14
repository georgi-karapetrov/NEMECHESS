#include "MovesListModel.h"

MovesListModel::MovesListModel( QObject* parent )
    : QAbstractListModel( parent ),
      m_movesVector( QVector< Movement* >( 0 ) )

{
    m_lastRowClicked = this->rowCount();
}

int MovesListModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent );
    return 1;
}

int MovesListModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent );
    return m_movesVector.size();
}

bool MovesListModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if ( index.isValid() && role == Qt::EditRole )
    {
        Q_UNUSED( value )
//        m_list.insert( index.row(), value.toString() );

//        emit ( dataChanged( index, index ) );
        return true;
    }
    return false;
}

QVariant MovesListModel::data( const QModelIndex& index, int role ) const
{
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
        if ( index.row() >= 0 && index.row() < m_movesVector.size() )
        {
//            qDebug() << "We have a vaild index";
            if ( m_movesVector.at( index.row() ) != 0 )
              return m_movesVector.at( index.row() )->toChessNotation();
        }
//        qDebug() << "Size of the vector:" << m_movesVector.size();
        return QVariant();

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

void MovesListModel::addMove( const QString& move )
{
    QModelIndex index = createIndex( 0, 0 );
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
//    auto iter = m_list.begin();
//    ++ iter; // something important going on here; gotta work it out
//    for ( int i = 0; i < m_lastRowClicked - 1; ++ i )
//    {
//        ++ iter;
//    }
//    m_list.erase( iter, --m_list.end() );
}

void MovesListModel::combineUndoRedo( const QStack< Movement* >* undoMoves, const QStack< Movement* >* redoMoves )
{
    if ( ! m_movesVector.isEmpty() )
    {
        m_movesVector.clear();
    }

    QStack< Movement* > tmpStack = *undoMoves;

    m_movesVector.resize( undoMoves->size() + redoMoves->size()  );
    qDebug() << m_movesVector.size();
    for ( int i = undoMoves->size() - 1; i >= 0; -- i )
    {
        m_movesVector[ i ] = tmpStack.pop();
    }

    tmpStack = *redoMoves;

   for ( int i = 0; i < redoMoves->size(); ++ i )
    {
        m_movesVector[ i + undoMoves->size() ] = tmpStack.pop();
    }

   this->refresh();

//    QModelIndex index = createIndex( 0, 0 );


}

void MovesListModel::setMovesVector( const QVector< Movement* >& movesVector )
{
    m_movesVector = movesVector;
}

QVector< Movement* > MovesListModel::movesVector() const
{
    return m_movesVector;
}

void MovesListModel::refresh()
{
    QModelIndex topLeft = createIndex( 0, 0 );
    QModelIndex bottomRight = createIndex( m_movesVector.size(), 0 );

    emit( dataChanged( topLeft, bottomRight ) );
}
