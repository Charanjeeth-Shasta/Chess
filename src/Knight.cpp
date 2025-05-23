#include "Knight.h"
#include <cstdlib>

bool Knight::isValidMove(Move move, Piece board[8][8]) {
    int dr = abs(move.to.row - move.from.row);
    int dc = abs(move.to.col - move.from.col);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}