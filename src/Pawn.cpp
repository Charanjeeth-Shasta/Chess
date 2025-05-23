#include "Pawn.h"
#include <cstdlib>

bool Pawn::isValidMove(Move move, Color color, Piece board[8][8], int enPassantRow, int enPassantCol, Color enPassantColor)
{
    int direction = (color == Color::WHITE) ? -1 : 1;
    int startRow = (color == Color::WHITE) ? 6 : 1;
    int dr = move.to.row - move.from.row;
    int dc = abs(move.to.col - move.from.col);

    // Move forward one square
    if (dr == direction && dc == 0 && board[move.to.row][move.to.col].type == PieceType::EMPTY)
        return true;

    // Move forward two squares from starting position
    if (move.from.row == startRow && dr == 2 * direction && dc == 0 &&
        board[move.to.row][move.to.col].type == PieceType::EMPTY &&
        board[move.from.row + direction][move.from.col].type == PieceType::EMPTY)
        return true;

    // Diagonal capture
    if (dr == direction && dc == 1 && board[move.to.row][move.to.col].type != PieceType::EMPTY &&
        board[move.to.row][move.to.col].color != color)
        return true;

    // En passant capture
    if (dr == direction && dc == 1 && move.to.row == enPassantRow && move.to.col == enPassantCol && enPassantColor != color && enPassantColor != Color::NONE)
    {
        return true;
    }

    return false;
}