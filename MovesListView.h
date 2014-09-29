#ifndef MOVESLISTVIEW_H
#define MOVESLISTVIEW_H

#include <QListView>
#include <QStandardItemModel>
#include <QDebug>

#include "PiecesManipulator.h"

using namespace Chess::GameLogic::GameComponents;

class MovesListView : public QListView
{
    Q_OBJECT
public:
    explicit MovesListView( PiecesManipulator* manipulator, QWidget *parent = 0);

    void addMove( const QString& move );

    void setManipulator( PiecesManipulator* manipulator );
    PiecesManipulator* manipulator() const;

public slots:
    void listItemClicked( QModelIndex index );

private:
    QWidget*            m_parent;
    QStandardItemModel* m_listModel;
    PiecesManipulator*  m_manipulator;
};

#endif // MOVESLISTVIEW_H
