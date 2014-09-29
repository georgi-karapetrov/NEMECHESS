#ifndef BOARD_H
#define BOARD_H

#include "ChessPiece.h"
//#include <iostream>
#include <vector>
#include <unordered_map>

namespace Chess{
namespace ChessComponents{
namespace PlayField{

using std::cout;
using std::endl;

using namespace Chess::ChessComponents::ChessPieces;

class Board
{
public:
    Board( const int rows       =  8,
           const int columns    =  8,
           const int cellWidth  = 50,
           const int cellHeight = 50 );
    Board( const Board& other );

    ~Board();

    void setRows( const int rows );
    int rows() const;

    void setColumns( const int columns );
    int columns() const;

    void setCellWidth( const int cellWidth );
    int cellWidth() const;

    void setCellHeight( const int cellHeight );
    int cellHeight() const;

    void setPiecesMap( const unordered_map< Position, ChessPiece* >& piecesMap );
    unordered_map< Position, ChessPiece* > piecesMap() const;

    void addPiece( ChessPiece* piece );
    bool movePiece( const Position& from, const Position& to );

    bool placePieces( vector < ChessPiece* > pieces,
                      unsigned int it );

    bool isValidPosition( const Position& position ) const;

    void initPiecesMap();

    void display();

    Position nextPosition( const Position& position );
    bool isThreat( ChessPiece* piece );
    bool inLoS( const Position& position, vector< ChessPiece* > aVector ) const;

    bool isPiece( const Position& position ) const;
    bool isAlly( const Position& position, const Colour& colour ) const;

    ChessPiece* pieceAt( const Position& position ) const;

    void setPassedMoves(ChessPiece* piece , int anInteger );
    int passedMoves( ChessPiece* piece ) const;

    void setWhitePieces( vector< ChessPiece* > pieces );
    vector< ChessPiece* > whitePieces() const;

    void setBlackPieces( vector< ChessPiece* > pieces );
    vector< ChessPiece* > blackPieces() const;


private:
    void clearPosition( const Position& position );
    void copy( const Board& other );

public:
    unordered_map< ChessPiece*, int > m_movesCountMap;

private:
    int m_rows;
    int m_columns;
    int m_cellWidth;
    int m_cellHeight;

    vector< ChessPiece* > m_whitePieces;
    vector< ChessPiece* > m_blackPieces;
    unordered_map< Position, ChessPiece* > m_piecesMap;
};

}
}
}

#endif // BOARD_H
