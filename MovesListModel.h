#ifndef MOVESLISTMODEL_H
#define MOVESLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QColor>

class MovesListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MovesListModel( QObject* parent = 0 );

    virtual int columnCount( const QModelIndex& parent ) const;
    virtual int rowCount( const QModelIndex& parent ) const;

    virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;

    void addMove( const QString& move );

private:
    public:
    QStringList m_list;
};

#endif // MOVESLISTMODEL_H
