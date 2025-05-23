#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "enums.h"
#include "Position.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

class ChessBoard
{
private:
    Piece board[8][8];
    Color currentTurn;
    bool gameOver;
    Position whiteKing, blackKing;
    Pawn pawn;
    Knight knight;
    Bishop bishop;
    Rook rook;
    Queen queen;
    King king;
    // En passant tracking
    int enPassantCol = -1; // Column where en passant is possible, -1 if not
    int enPassantRow = -1; // Row of the pawn that can be captured en passant
    Color enPassantColor = Color::NONE;

public:
    ChessBoard();
    void resetBoard();
    void displayBoard();
    bool isValidPosition(Position pos);
    bool isValidMove(Move move);
    bool makeMove(Move move);
    bool isCheckmate();
    bool isGameOver();
    Color getCurrentTurn();
    // En passant accessors
    int getEnPassantCol() const { return enPassantCol; }
    int getEnPassantRow() const { return enPassantRow; }
    Color getEnPassantColor() const { return enPassantColor; }
    void setEnPassant(int row, int col, Color color)
    {
        enPassantRow = row;
        enPassantCol = col;
        enPassantColor = color;
    }
    void clearEnPassant()
    {
        enPassantRow = -1;
        enPassantCol = -1;
        enPassantColor = Color::NONE;
    }
};

#endif