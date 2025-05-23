#ifndef BISHOP_H
#define BISHOP_H
#include "Position.h"
#include "Piece.h"

class Bishop {
public:
    bool isValidMove(Move move, Piece board[8][8]);
};

#endif