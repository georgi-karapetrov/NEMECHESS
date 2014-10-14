#ifndef MOVESLISTMODEL_H
#define MOVESLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QColor>
#include <QDebug>
#include <QStack>

#include "Movement.h"
#include "Position.h"

using namespace Chess::GameLogic::Movements;

class MovesListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MovesListModel( QObject* parent = 0 );

    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;

    virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;

    virtual Qt::ItemFlags flags( const QModelIndex& index ) const;

    void setMovesVector( const QVector< Movement* >& movesVector );
    QVector< Movement* > movesVector() const;

    QString toChessNotation( const Position& position );
    void addMove( const QString& move );

    void setLastRowClicked( const int& row );
    int lastRowClicked() const;

    void refresh();

    void clearRedoMoves();

    void combineUndoRedo(const QStack<Movement *> *undoMoves, const QStack<Movement *> *redoMoves );

private:
    QStringList          m_list;           // #I am full of brilliant ideas
    int                  m_lastRowClicked; // polymerization between the undo and redo stacks
    QVector< Movement* > m_movesVector;
};

#endif // MOVESLISTMODEL_H

