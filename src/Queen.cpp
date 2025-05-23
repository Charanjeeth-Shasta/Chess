#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include <cstdlib>

bool Queen::isValidMove(Move move, Piece board[8][8]) {
    Bishop bishop;
    Rook rook;
    return bishop.isValidMove(move, board) || rook.isValidMove(move, board);
}