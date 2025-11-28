#include "hero.h"
#include <iostream>
using namespace std;

Hero::Hero()
    : name("User"),
    health(3),
    maxHealth(3),
    attackRange(1),
    attack(1),
    x(0),
    y(0),
    moveController(x, y),
    world(nullptr)
{
}

Hero::Hero(string n, int hp, int range, int startX, int startY)
    : name(n),
    health(hp),
    maxHealth(hp),
    attackRange(range),
    attack(1),
    x(startX),
    y(startY),
    moveController(x, y),
    world(nullptr)
{
}

bool Hero::move(Direction dir, const Map& map, const vector<Enemy*>& enemies) {
    return moveController.move(dir, map, enemies);
}

void Hero::drawStatus() const {
    cout << "HP: " << health << "/" << maxHealth
        << "   RANGE: " << attackRange
        << "   ATK: " << attack;
}
