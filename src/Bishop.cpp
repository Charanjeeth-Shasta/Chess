#include "Bishop.h"
#include <cstdlib>

bool Bishop::isValidMove(Move move, Piece board[8][8]) {
    int dr = abs(move.to.row - move.from.row);
    int dc = abs(move.to.col - move.from.col);
    if (dr != dc) return false;

    int rowStep = (move.to.row > move.from.row) ? 1 : -1;
    int colStep = (move.to.col > move.from.col) ? 1 : -1;
    for (int i = 1; i < dr; i++) {
        if (board[move.from.row + i * rowStep][move.from.col + i * colStep].type != PieceType::EMPTY)
            return false;
    }
    return true;
}