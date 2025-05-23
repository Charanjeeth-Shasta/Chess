#include "King.h"
#include <cstdlib>

bool King::isValidMove(Move move, Piece board[8][8]) {
    int dr = abs(move.to.row - move.from.row);
    int dc = abs(move.to.col - move.from.col);
    return (dr <= 1 && dc <= 1) && (dr + dc > 0);
}