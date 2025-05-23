#ifndef KNIGHT_H
#define KNIGHT_H
#include "Position.h"
#include "Piece.h"

class Knight {
public:
    bool isValidMove(Move move, Piece board[8][8]);
};

#endif