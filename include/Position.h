#ifndef POSITION_H
#define POSITION_H

struct Position {
    int row;
    int col;
};

struct Move {
    Position from;
    Position to;
};

#endif