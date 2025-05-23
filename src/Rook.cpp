#include "Rook.h"
#include <cstdlib>

bool Rook::isValidMove(Move move, Piece board[8][8]) {
    int dr = move.to.row - move.from.row;
    int dc = move.to.col - move.from.col;
    if (dr != 0 && dc != 0) return false;

    int step, steps;
    int rowStep = 0, colStep = 0;
    if (dr != 0) {
        rowStep = (dr > 0) ? 1 : -1;
        steps = abs(dr);
    } else {
        colStep = (dc > 0) ? 1 : -1;
        steps = abs(dc);
    }

    for (int i = 1; i < steps; i++) {
        if (board[move.from.row + i * rowStep][move.from.col + i * colStep].type != PieceType::EMPTY)
            return false;
    }
    return true;
}