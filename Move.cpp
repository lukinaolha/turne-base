#include "Move.h"

Move::Move(int& rx, int& ry) : x(rx), y(ry) {}

bool Move::move(Direction dir, const Map& map) {
    int nx = x;
    int ny = y;

    switch (dir) {
    case Direction::Up:    ny--; break;
    case Direction::Down:  ny++; break;
    case Direction::Left:  nx--; break;
    case Direction::Right: nx++; break;
    case Direction::None:  return false;
    }

    if (!map.isInside(nx, ny)) return false;
    if (!map.canEnter(nx, ny)) return false;

    x = nx;
    y = ny;
    return true;
}
