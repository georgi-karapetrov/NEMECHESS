#include "Board.h"
#include "ChessPiece.h"

using namespace Chess::ChessComponents::PlayField;

Board::Board(const int rows,
             const int columns ,
             const int cellWidth,
             const int cellHeight )
    : m_rows ( rows ),
      m_columns ( columns ),
      m_cellWidth( cellWidth ),
      m_cellHeight( cellHeight )
{
    initPiecesMap();
}

Board::~Board()
{
    cout << "~Board()\n";
    m_movesCountMap.clear();
    m_piecesMap.clear();
    for ( auto iter = m_whitePieces.begin(); iter != m_whitePieces.end(); ++ iter )
    {
        delete *iter;
    }

    for ( auto iter = m_blackPieces.begin(); iter != m_blackPieces.end(); ++ iter )
    {
        delete *iter;
    }
}

Board::Board( const Board& other )
{
    copy ( other );
}

void Board::setRows( const int rows )
{
    m_rows = rows;
}

int Board::rows() const
{
    return m_rows;
}

void Board::setColumns( const int columns )
{
    m_columns = columns;
}

int Board::columns() const
{
    return m_columns;
}

void Board::setCellWidth( const int cellWidth )
{
    m_cellWidth = cellWidth;
}

int Board::cellWidth() const
{
    return m_cellWidth;
}

void Board::setCellHeight( const int cellHeight )
{
    m_cellHeight = cellHeight;
}

int Board::cellHeight() const
{
    return m_cellHeight;
}

void Board::setPiecesMap( const unordered_map< Position, ChessPiece* >& piecesMap )
{
    m_piecesMap = piecesMap;
}

unordered_map< Position, ChessPiece* > Board::piecesMap() const
{
    return m_piecesMap;
}

void Board::copy( const Board& other )
{
    m_whitePieces = other.m_whitePieces;
    m_blackPieces = other.m_blackPieces;
    m_piecesMap = other.m_piecesMap;

    m_rows = other.m_rows;
    m_columns = other.m_columns;
}

void Board::display()
{
    int width = 0;
    for ( Position pos( 0, 0 ); pos != Position ( m_columns, m_rows ); pos = nextPosition( pos ) )
    {
        if ( isValidPosition( pos ) )
        {
            m_piecesMap[ pos ] == 0 ? cout << "# " : cout << m_piecesMap [ pos ]->m_sigil << " ";

            width++;
            if ( width == m_columns )
            {
                width = 0;
                cout << endl;
            }
        }
        else
        {
            break;
        }
    }
}

bool Board::isValidPosition( const Position& position ) const
{

    return    position.x() >= 0
           && position.x() < m_columns
           && position.y() >= 0
           && position.y() < m_rows;
}

bool Board::isPiece( const Position& position ) const
{
    unordered_map< Position, ChessPiece* >::const_iterator iter = m_piecesMap.find( position );

    if ( iter == m_piecesMap.end() )
    {
        return false;
    }

    return iter->second != 0;
}

bool Board::isObstacle( const Position& position, const Colour& colour ) const
{
    unordered_map< Position, ChessPiece* >::const_iterator iter = m_piecesMap.find( position );

    return isPiece( position ) && iter->second->colour() == colour;
}

void Board::addPiece( ChessPiece* piece )
{
    if ( isValidPosition( piece->position() ) )
    {
        m_piecesMap[ piece->position() ] = piece;
        piece->colour() == white ? m_whitePieces.push_back( piece ) : m_blackPieces.push_back( piece );
        m_movesCountMap[ piece ] = 0;
    }

    // add it to map
    // add it to colours vectors.

}


bool Board::movePiece( const Position& from, const Position& to )
{
    if ( m_piecesMap[ from ] == 0
         || !this->isValidPosition( from )
         || !this->isValidPosition( to ) )
    {
        return false;
    }

    m_piecesMap[ from ]->setPosition( to );
    m_piecesMap[ to ] = m_piecesMap[ from ];
    m_piecesMap[ from ] = 0;

    return true;
}

void Board::setWhitePieces( vector< ChessPiece* > pieces )
{
    m_whitePieces = pieces;
}

vector< ChessPiece* > Board::whitePieces() const
{
    return m_whitePieces;
}

void Board::setBlackPieces( vector< ChessPiece* > pieces )
{
    m_blackPieces = pieces;
}

vector< ChessPiece* > Board::blackPieces() const
{
    return m_blackPieces;
}

bool Board::placePieces( vector < ChessPiece* > pieces,
                        unsigned int index )
{
    if ( index == pieces.size() )
    {
        return true;
    }
    vector< ChessPiece* >tmpPieces( index );
    std::copy( pieces.begin(), pieces.begin() + index, tmpPieces.begin() ); //is this really the better way, obi-wan?

    for ( int i = 0; i < this->columns(); i++ )
    {
        for ( int j = 0; j < this->rows(); j++ )
        {
            if ( m_piecesMap[ Position( i, j ) ] == 0  )
            {
                pieces[ index ]->setPosition( Position( i, j ) );
                const bool threat = this->isThreat( pieces[ index ] );
                const bool los = this->inLoS( Position( i, j ), tmpPieces );
                if ( index == 0 || !( los
                                      || threat ) )
                {
                    addPiece( pieces[ index ] );

                    if ( placePieces( pieces, ++index ) )
                    {
                        return true;
                    }

                    this->clearPosition( Position( i, j ) );
                    --index;
                }
            }
        }
    }
    return false;
}

bool Board::isThreat( ChessPiece* piece )
{
    vector < Position > tmp = piece->allowedMovements();
    for ( unsigned int i = 0; i < tmp.size(); ++i )
    {
        if ( m_piecesMap[ tmp[ i ] ] != 0 )
        {
           // cout << "I see something at " << piece->getPosition() << endl;
            return true;
        }
    }
    return false;
}

bool Board::inLoS( const Position& position, vector < ChessPiece* > aVector ) const
{
    if ( !aVector.empty() )
    {
        for ( unsigned int i = 0; i < aVector.size(); i++ )
        {
            vector < Position > helper = aVector[ i ]->allowedMovements();
            for ( unsigned int j = 0; j < helper.size(); j++ )
            {
                if ( position == helper[ j ] )
                {
                   // cout << "Something sees me. I am at " << position << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

Position Board::nextPosition( const Position& position )
{
    if ( position.x() == m_columns && position.y() == m_rows )
    {
        return Position ( position.x() - 1, position.y() - 1 );
    }

    if ( position.x() == m_columns - 1 && position.y() < m_rows - 1 )
    {
        return Position( 0, position.y() + 1 );
    }

    return Position( position.x() + 1, position.y() );
}

void Board::clearPosition( const Position& position )
{
    //cout << "Bye-bye, cruel world! Pick my body from " << position << endl;
    m_piecesMap[ position ] = 0;

}

void Board::initPiecesMap()
{
    for ( int i = 0; i < m_columns; i++ )
    {
        for ( int j = 0; j < m_rows; j++ )
        {
            m_piecesMap [ Position( i, j ) ] = 0;
        }
    }
}

ChessPiece* Board::pieceAt( const Position& position ) const
{
    unordered_map< Position, ChessPiece* >::const_iterator iter = m_piecesMap.find( position );

    if ( iter == m_piecesMap.end() )
    {
        return 0;
    }

    return iter->second;
}

void Board::setPassedMoves( ChessPiece* piece, int anInteger )
{
    m_movesCountMap[ piece ] = anInteger;
}

int Board::passedMoves( ChessPiece* piece ) const
{
    unordered_map< ChessPiece*, int >::const_iterator iter = m_movesCountMap.find( piece );

    if ( iter == m_movesCountMap.end() )
    {
        return -1;
    }

    return iter->second;
}
