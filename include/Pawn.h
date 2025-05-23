#ifndef PAWN_H
#define PAWN_H
#include "enums.h"
#include "Position.h"
#include "Piece.h"

class Pawn
{
public:
    bool isValidMove(Move move, Color color, Piece board[8][8], int enPassantRow = -1, int enPassantCol = -1, Color enPassantColor = Color::NONE);
};

#endif