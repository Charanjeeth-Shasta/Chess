#include "Board.h"
#include <iostream>

using namespace std;

ChessBoard::ChessBoard()
{
    resetBoard();
    currentTurn = Color::WHITE;
    gameOver = false;
    whiteKing = {7, 4};
    blackKing = {0, 4};
}

void ChessBoard::resetBoard()
{
    // Initialize empty squares
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = {PieceType::EMPTY, Color::NONE};

    // Set up white pieces
    board[7][0] = {PieceType::ROOK, Color::WHITE};
    board[7][1] = {PieceType::KNIGHT, Color::WHITE};
    board[7][2] = {PieceType::BISHOP, Color::WHITE};
    board[7][3] = {PieceType::QUEEN, Color::WHITE};
    board[7][4] = {PieceType::KING, Color::WHITE};
    board[7][5] = {PieceType::BISHOP, Color::WHITE};
    board[7][6] = {PieceType::KNIGHT, Color::WHITE};
    board[7][7] = {PieceType::ROOK, Color::WHITE};
    for (int j = 0; j < 8; j++)
        board[6][j] = {PieceType::PAWN, Color::WHITE};

    // Set up black pieces
    board[0][0] = {PieceType::ROOK, Color::BLACK};
    board[0][1] = {PieceType::KNIGHT, Color::BLACK};
    board[0][2] = {PieceType::BISHOP, Color::BLACK};
    board[0][3] = {PieceType::QUEEN, Color::BLACK};
    board[0][4] = {PieceType::KING, Color::BLACK};
    board[0][5] = {PieceType::BISHOP, Color::BLACK};
    board[0][6] = {PieceType::KNIGHT, Color::BLACK};
    board[0][7] = {PieceType::ROOK, Color::BLACK};
    for (int j = 0; j < 8; j++)
        board[1][j] = {PieceType::PAWN, Color::BLACK};
}

void ChessBoard::displayBoard()
{
    cout << "\n  a b c d e f g h\n";
    for (int i = 0; i < 8; i++)
    {
        cout << 8 - i << " ";
        for (int j = 0; j < 8; j++)
        {
            Piece p = board[i][j];
            char symbol;
            switch (p.type)
            {
            case PieceType::PAWN:
                symbol = 'P';
                break;
            case PieceType::KNIGHT:
                symbol = 'N';
                break;
            case PieceType::BISHOP:
                symbol = 'B';
                break;
            case PieceType::ROOK:
                symbol = 'R';
                break;
            case PieceType::QUEEN:
                symbol = 'Q';
                break;
            case PieceType::KING:
                symbol = 'K';
                break;
            default:
                symbol = '.';
                break;
            }
            if (p.color == Color::WHITE)
                symbol = tolower(symbol);
            cout << symbol << ' ';
        }
        cout << 8 - i << endl;
    }
    cout << "  a b c d e f g h\n\n";
}

bool ChessBoard::isValidPosition(Position pos)
{
    return pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8;
}

bool ChessBoard::isValidMove(Move move)
{
    if (!isValidPosition(move.from) || !isValidPosition(move.to))
        return false;

    Piece piece = board[move.from.row][move.from.col];
    if (piece.color != currentTurn || piece.type == PieceType::EMPTY)
        return false;

    Piece target = board[move.to.row][move.to.col];
    if (target.color == piece.color && target.type != PieceType::EMPTY)
        return false;

    switch (piece.type)
    {
    case PieceType::PAWN:
        return pawn.isValidMove(move, piece.color, board, enPassantRow, enPassantCol, enPassantColor);
    case PieceType::KNIGHT:
        return knight.isValidMove(move, board);
    case PieceType::BISHOP:
        return bishop.isValidMove(move, board);
    case PieceType::ROOK:
        return rook.isValidMove(move, board);
    case PieceType::QUEEN:
        return queen.isValidMove(move, board);
    case PieceType::KING:
        return king.isValidMove(move, board);
    default:
        return false;
    }
}

bool ChessBoard::makeMove(Move move)
{
    // Debug: Print the type and color of the destination square before the move
    std::cout << "DEBUG: Before move, board[" << move.to.row << "][" << move.to.col << "] type=" << (int)board[move.to.row][move.to.col].type << ", color=" << (int)board[move.to.row][move.to.col].color << std::endl;
    if (!isValidMove(move))
        return false;

    // Update king position if moving king
    if (board[move.from.row][move.from.col].type == PieceType::KING)
    {
        if (board[move.from.row][move.from.col].color == Color::WHITE)
            whiteKing = move.to;
        else
            blackKing = move.to;
    }

    // En passant logic
    Piece movingPiece = board[move.from.row][move.from.col];
    if (movingPiece.type == PieceType::PAWN)
    {
        // If pawn moves two squares, set en passant
        if (abs(move.to.row - move.from.row) == 2)
        {
            setEnPassant((move.from.row + move.to.row) / 2, move.from.col, movingPiece.color);
        }
        else
        {
            // En passant capture
            if (move.to.col != move.from.col && board[move.to.row][move.to.col].type == PieceType::EMPTY &&
                move.to.row == enPassantRow && move.to.col == enPassantCol && enPassantColor != movingPiece.color && enPassantColor != Color::NONE)
            {
                int capturedRow = (movingPiece.color == Color::WHITE) ? move.to.row + 1 : move.to.row - 1;
                board[capturedRow][move.to.col] = {PieceType::EMPTY, Color::NONE};
            }
            clearEnPassant();
        }
    }
    else
    {
        clearEnPassant();
    }

    // Move piece
    board[move.to.row][move.to.col] = board[move.from.row][move.from.col];
    board[move.from.row][move.from.col] = {PieceType::EMPTY, Color::NONE};

    // Check for checkmate
    if (isCheckmate())
    {
        gameOver = true;
        cout << (currentTurn == Color::WHITE ? "Black" : "White") << " wins by checkmate!\n";
    }

    currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    return true;
}

bool ChessBoard::isCheckmate()
{
    Position kingPos = (currentTurn == Color::WHITE) ? whiteKing : blackKing;
    // Simple check for opponent's ability to attack king
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].color != currentTurn && board[i][j].type != PieceType::EMPTY)
            {
                Move move = {{i, j}, kingPos};
                if (isValidMove(move))
                    return true;
            }
        }
    }
    return false;
}

bool ChessBoard::isGameOver() { return gameOver; }

Color ChessBoard::getCurrentTurn() { return currentTurn; }