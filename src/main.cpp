#include <iostream>
#include <string>
#include <cctype>
#include "Board.h"
#include "Position.h"

using namespace std;

Move parseMove(string input) {
    Move move;
    if (input.length() != 4) return move;
    move.from.col = tolower(input[0]) - 'a';
    move.from.row = 8 - (input[1] - '0');
    move.to.col = tolower(input[2]) - 'a';
    move.to.row = 8 - (input[3] - '0');
    return move;
}

int main() {
    ChessBoard game;
    string input;

    cout << "Welcome to Two-Player Chess!\n";
    cout << "Enter moves in format 'e2e4' (from-to). Enter 'quit' to exit.\n";
    cout << "White moves first. Lowercase pieces are white, uppercase are black.\n";

    while (!game.isGameOver()) {
        game.displayBoard();
        cout << (game.getCurrentTurn() == Color::WHITE ? "White" : "Black") << "'s turn: ";
        cin >> input;

        if (input == "quit") break;

        Move move = parseMove(input);
        if (!game.makeMove(move)) {
            cout << "Invalid move! Try again.\n";
        }
    }

    if (game.isGameOver()) {
        cout << "Game Over!\n";
    } else {
        cout << "Game ended by user.\n";
    }

    return 0;
}