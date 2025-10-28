#include "hero.h"
#include <iostream>
using namespace std;

Hero::Hero()
    : name("User"), health(3), maxHealth(3),
    attackRange(1), x(0), y(0),
    moveController(x, y) {
}

Hero::Hero(string n, int hp, int range, int startX, int startY)
    : name(n), health(hp), maxHealth(hp),
    attackRange(range), x(startX), y(startY),
    moveController(x, y) {
}

bool Hero::move(Direction dir, const Map& map) {
    return moveController.move(dir, map);
}

void Hero::drawStatus() const {
    cout << "HP: " << health << "/" << maxHealth
        << "   RANGE: " << attackRange;
}
