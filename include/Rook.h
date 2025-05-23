#ifndef ROOK_H
#define ROOK_H
#include "Position.h"
#include "Piece.h"

class Rook {
public:
    bool isValidMove(Move move, Piece board[8][8]);
};

#endif