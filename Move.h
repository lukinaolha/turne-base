#pragma once
#include "Map.h"

class Enemy;

enum class Direction {
    Up,
    Down,
    Left,
    Right,
    None
};

class Move {
private:
    int& x, & y;

public:
    Move(int& rx, int& ry);

    bool move(Direction dir, const Map& map, const vector<Enemy*>& enemies);

};
