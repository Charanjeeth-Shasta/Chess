#ifndef QUEEN_H
#define QUEEN_H
#include "Position.h"
#include "Piece.h"

class Queen {
public:
    bool isValidMove(Move move, Piece board[8][8]);
};

#endif