#ifndef KING_H
#define KING_H
#include "Position.h"
#include "Piece.h"

class King {
public:
    bool isValidMove(Move move, Piece board[8][8]);
};

#endif