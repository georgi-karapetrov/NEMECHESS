 #include "GameEngine.h"

using namespace Chess::GameLogic::GameComponents;

GameEngine::GameEngine( const int rows,
                        const int columns,
                        const int cellWidth,
                        const int cellHeght,
                        const int numberOfPlayers,
                        Colour startingColour )
    : QObject( 0 ),
      m_board( new Board( rows, columns, cellWidth, cellHeght ) ),
      m_manipulator( m_board ),
      m_currentPlayerColour( startingColour ),
      m_quit( false ),
      m_isFigureSelected( false ),
      m_isFirstClick( true ),
      m_inCheckFlag( false )
{
    m_widget = new Widget( 0 );
    qDebug() << "Widget created";

    m_model =  new MovesListModel( this );
    qDebug() << "Model created";

    m_undoMoves.push( new StartGameMovement( m_board ) );
    m_model->combineUndoRedo( &m_undoMoves, &m_redoMoves );

    m_manipulator.setUndoMoves( &m_undoMoves );
    m_manipulator.setRedoMoves( &m_redoMoves );
    qDebug() << "Undo/Redo set";

    connect( m_widget, SIGNAL(clickCell(QPoint)), this, SLOT(clickCellListener(QPoint)));
    connect( this, SIGNAL(jobFinished()), m_widget, SLOT(repaint()) );
    connect( m_widget->view(), SIGNAL(clicked(QModelIndex)), this, SLOT(onMovesViewClicked(QModelIndex)) );
    connect( this, SIGNAL(figureSelected(Position)), m_widget, SLOT(figureSelectedListener(Position)) );

    qDebug() << "All slots connected";

    m_widget->setInterface( BoardInterface ( m_board ) );
    m_widget->setMovesListModel( m_model );
        qDebug() << "Interface and model set";
    m_model->refresh();

    m_widget->view()->setGeometry( BoardInterface::X_OFFSET * 3 + m_board->columns() * m_board->cellWidth(),
                                   BoardInterface::Y_OFFSET,
                                   200,
                                   m_board->rows() * m_board->cellHeight() );
    m_widget->view()->setEditTriggers( QAbstractItemView::NoEditTriggers );
    m_widget->show();

    for ( int i = 0; i < numberOfPlayers; ++i )
    {
        Player* player = new Player( m_board, startingColour, &m_manipulator );

        qDebug() << "Manipulator created at:" << player->manipulator() << "Should be:" << &m_manipulator;
        player->setManipulator( &m_manipulator );


        qDebug() << "Address set to:" << player->manipulator();
        m_players.push_back( player );

        startingColour = nextColour( startingColour );
    }
}


GameEngine::~GameEngine()
{
    cout << "~GameEngine()\n";
    delete m_widget;
    this->destroy();
}

void GameEngine::destroy()
{
    //this->disposeOfPieceVectors();
    delete m_board;
}

void GameEngine::setBoard( Board* const board )
{
    m_board = board;
}

Board* GameEngine::board() const
{
    return m_board;
}

void GameEngine::setManipulator( const PiecesManipulator& manipulator )
{
    m_manipulator = manipulator;
}

PiecesManipulator GameEngine::manipulator() const
{
    return m_manipulator;
}

void GameEngine::setModel( MovesListModel* model )
{
    m_model = model;
}

MovesListModel* GameEngine::model()
{
    return m_model;
}

void GameEngine::addPlayer( Player* player )
{
    player->setBoard( m_board );
    m_players.push_back( player );
}

void GameEngine::nextPlayersTurn()
{
    m_currentPlayerColour = nextColour( m_currentPlayerColour );
}

void GameEngine::run()
{
    this->setStandardGame();
//    this->setPiecesForTesting();
}

void GameEngine::clickCellListener( const QPoint& point )
{



    this->chewCoordinates( point );
    emit( jobFinished() );
}

void GameEngine::setPiecesForTesting()
{
    m_board->setRows( 8 );
    m_board->setColumns( 8 );

    ChessPiece* whiteQueen = new Queen( Position( 0, 7 ), Chess::black, m_board );
    m_board->addPiece( whiteQueen );

    ChessPiece* blackKing = new King( Position( 2, 7 ), Chess::white, m_board );
    m_board->addPiece( blackKing );

    ChessPiece* blackRook = new Rook( Position( 1, 7), Chess::white, m_board );
    m_board->addPiece( blackRook );
}

void GameEngine::setPiecesForStandardGame( const Colour& colour )
{
    m_board->setRows( 8 );
    m_board->setColumns( 8 );

    for ( int i = 0; i < 8; ++ i )
    {
        ChessPiece* pawn = new Pawn( Position( i, VERTICAL_OFFSET - 1 - colour * 5 ), colour, m_board );
        m_board->addPiece( pawn );
    }

    ChessPiece* rook = new Rook( Position ( ROOK_OFFSET, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( rook );
    rook = new Rook( Position ( ROOK_OFFSET + 7, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( rook );

    ChessPiece* knight = new Knight( Position( KNIGHT_OFFSET, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( knight );
    knight = new Knight( Position( KNIGHT_OFFSET + 5, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( knight );

    ChessPiece* bishop = new Bishop( Position( BISHOP_OFFSET, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( bishop );
    bishop = new Bishop( Position( BISHOP_OFFSET + 3, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( bishop );

    ChessPiece* queen = new Queen( Position( QUEEN_OFFSET, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( queen );

    ChessPiece* king = new King( Position( KING_OFFSET, VERTICAL_OFFSET - colour * VERTICAL_OFFSET ), colour, m_board );
    m_board->addPiece( king );

    //m_board->initMovesMap();
}

void GameEngine::setStandardGame()
{
    setPiecesForStandardGame( white );
    setPiecesForStandardGame( black );
//    m_board->display();
}

void GameEngine::parseInstructions( const string& instruction )
{
    const Instruction instr = instructionFromCode( tolower( instruction[ 0 ] ) );
    switch( instr )
    {
    case Quit:
        quit();
        break;
    case Move:
    {
        Position from = fromChessNotation( instruction[ 2 ], instruction[ 3 ] );
        Position to   = fromChessNotation( instruction[ 5 ], instruction[ 6 ] );

        Error errorCode = m_manipulator.makeAMove( from, to, m_currentPlayerColour );

        switch( errorCode )
        {
        case EmptyPosition:
            cout << "There's nothing there!\n";
            pressEnterToContinue();
            break;
        case WrongColour:
            cout << "Can't touch this!\n";
            pressEnterToContinue();
            break;
        case InvalidDestination:
            cout << "This can't go there!\n";
            pressEnterToContinue();
            break;
        case Check:
            cout << "You are in check!\nYour King is crying for help!\n";
            pressEnterToContinue();
            break;
        case Success:
            this->nextPlayersTurn();
            break;
        default:
            cout << "This output is unseen!\n";
        }
        break;
    }
    case Undo:
        m_manipulator.undo();
        this->nextPlayersTurn();
        break;
    case Pass:
        this->nextPlayersTurn();
        break;
//    case Castling:
        if ( instruction == "0-0-0"
             || instruction == "o-o-o"
             || instruction == "O-O-O" )
        {
           if ( !m_manipulator.castling( m_currentPlayerColour, QUEENSIDE_CASTLING ) )
           {
               cout << "QUEENSIDE_CASTLING castling isn't allowed under current circumstances!\n";
               pressEnterToContinue();
           }
        }
        else if ( instruction == "0-0"
                  || instruction == "o-o"
                  || instruction == "O-O" )
        {
            if ( !m_manipulator.castling( m_currentPlayerColour, KINGSIDE_CASTLING ) )
            {
                cout << "KINGSIDE_CASTLING castling isn't allowed under current circumstances!\n";
                pressEnterToContinue();
            }
        }
        else
        {
            cout << "\nUnrecognized Instruction!\n";
            pressEnterToContinue();
        }
        break;
    case FastForward:
        parseInstructions( "m,e2,e4" );
        parseInstructions( "p" );
        parseInstructions( "m,f1,e2" );
        parseInstructions( "p" );
        parseInstructions( "m,g1,h3" );
        parseInstructions( "p" );
        parseInstructions( "m,b1,a3" );
        parseInstructions( "p" );
        parseInstructions( "m,d2,d4" );
        parseInstructions( "p" );
        parseInstructions( "m,c1,e3" );
        parseInstructions( "p" );
        parseInstructions( "m,d1,d2" );
        parseInstructions( "p" );
        break;
    case Invalid:
        cout << "\nUnrecognized instruction!\n";
        break;
    default:
        cout << "woop-woop!\n";
        break;
    }
}

Instruction GameEngine::instructionFromCode( const char& ch )
{
    switch( ch )
    {
    case 'q':
        return Quit;
    case 'm':
        return Move;
    case 'u':
        return Undo;
    case 'p':
        return Pass;
    case '0':
    case 'o':
    case 'O':
//        return Castling;
    case 'f':
        return FastForward;
    }
    return Invalid;
}

Position GameEngine::fromChessNotation( const char& x, const char& y )
{
    return Position( x - 'a', m_board->rows() - ( y - '0' ) );
}

void GameEngine::quit()
{
    /*
     * exterminate( allPeople );
     * exterminate( blackRace );
     */

    // we have a badass over here
    m_quit |= 1; // hate as much as you want
}

void GameEngine::pressEnterToContinue()
{
    cout << "\nPress Enter to continue...\n";

    cin.ignore();
    cin.get();
}

Position GameEngine::toPosition( QPoint point )
{
    return Position( floor( ( point.x() - BoardInterface::X_OFFSET ) / m_board->cellWidth() ),
                     floor( ( point.y() - BoardInterface::Y_OFFSET ) / m_board->cellHeight() ) );
}

void GameEngine::chewCoordinates( const QPoint& point )
{
    Position position = toPosition( point );
    Player* currentPlayer = m_currentPlayerColour == Chess::white ? m_players[ 0 ] : m_players[ 1 ];

    if ( m_isFigureSelected )
    {
        m_to = position;

        Error makeAMoveOutcome = m_manipulator.makeAMove( m_from,
                                                          m_to,
                                                          m_currentPlayerColour );

        if ( makeAMoveOutcome == Success || makeAMoveOutcome == Castling )
        {
            Player* otherPlayer = currentPlayer == m_players[ 0 ] ? m_players[ 1 ] : m_players[ 0 ];

            if ( otherPlayer->isInCheck() )
            {
                m_manipulator.undoMoves()->top()->setFlags( CHECK_FLAG );
            }

            if ( currentPlayer->isInCheck() )
            {

                m_manipulator.undo( true ); // silent
                m_isFigureSelected = false;
                return;
            }

            if ( ! m_manipulator.redoMoves()->isEmpty() )
            {
                m_manipulator.flushRedo();
                m_model->clearRedoMoves();
            }

            m_model->combineUndoRedo( &m_undoMoves, &m_redoMoves );

            qDebug() << m_model->movesVector().at( 0 )->toChessNotation();

            m_widget->view()->clearSelection();
            m_model->setLastRowClicked( m_model->rowCount() - 1  );

            qDebug() << currentPlayer->isInCheck();
            this->nextPlayersTurn();
        }

        m_from = Position( -1, -1 );
        m_to   = Position( -1, -1 );
        m_isFigureSelected = false;

    } // if ( !isFigureSelected )
    else
    {
        if ( m_board->isPiece( position ) )
        {
            if ( m_board->pieceAt( position )->colour() != m_currentPlayerColour )
            {
                qDebug() << "Wrong colour!";
                return;
            }
            this->selectFigure( position );
        }
    }
}

void GameEngine::onMovesViewClicked( const QModelIndex& index )
{
    if ( index.row() < m_model->lastRowClicked() )
    {
        for ( int i = index.row(); i < m_model->lastRowClicked(); ++ i ) // '<' and '<='
        {
            if ( m_manipulator.undo() )
            {
                this->nextPlayersTurn();
            }
        }
        m_isFirstClick = false;
    }
    else if ( index.row() > m_model->lastRowClicked() )
    {
        m_isFirstClick = true;
        for ( int i = m_model->lastRowClicked(); i < index.row(); ++ i ) // '<' to '<='
        {
            if ( m_manipulator.redo() )
            {
                this->nextPlayersTurn();
            }
        }
    }
    m_model->setLastRowClicked( index.row() );
    emit( jobFinished() );
}

void GameEngine::selectFigure( const Position& position )
{
    m_from = position;
    m_isFigureSelected = true;
    qDebug() << "Position taken as:" << position.x() << position.y();
    emit figureSelected( position );
}

void GameEngine::disposeOfPieceVectors()
{

}

// TODO: Pawn promotion

//void run_old()
//{
//    string instruction;
//    while ( !m_quit )
//    {
//        cout << ">>> ";
//        cin >> instruction;

//        parseInstructions( instruction );
//        cin.clear();
//        //cin.ignore();
//        //cin.flush();

//        system( "clear" );

//        m_board->display();
//    }
//}
