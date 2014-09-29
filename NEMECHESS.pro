#-------------------------------------------------
#
# Project created by QtCreator 2014-09-23T16:45:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NEMECHESS
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        Widget.cpp \
    Bishop.cpp \
    Board.cpp \
    ChessPiece.cpp \
    ComplexMovement.cpp \
    GameEngine.cpp \
    King.cpp \
    Knight.cpp \
    Movement.cpp \
    Pawn.cpp \
    PiecesManipulator.cpp \
    Player.cpp \
    Position.cpp \
    PositionResolver.cpp \
    Queen.cpp \
    Rook.cpp \
    SimpleMovement.cpp \
    ChessPieceInterface.cpp \
    BoardInterface.cpp \
    MovesListView.cpp

HEADERS  += Widget.h \
    Bishop.h \
    Board.h \
    ChessPiece.h \
    ComplexMovement.h \
    GameEngine.h \
    King.h \
    Knight.h \
    Movement.h \
    Pawn.h \
    PiecesManipulator.h \
    Player.h \
    Position.h \
    PositionResolver.h \
    Queen.h \
    Rook.h \
    SimpleMovement.h \
    ChessPieceInterface.h \
    BoardInterface.h \
    MovesListView.h

OTHER_FILES += \
    NEMECHESS.pro.user
