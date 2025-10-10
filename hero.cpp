#include "hero.h"
#include "Map.h"
#include <iostream>
#include <cctype>
using namespace std;

Hero::Hero(string n, int hp, int range, int startX, int startY)
    : name(n), health(hp), maxHealth(hp), attackRange(range), x(startX), y(startY) {
}

bool Hero::move(char direction, const Map& map) {
    
    int newX = x;
    int newY = y;

    switch (toupper(direction)) {
    case 'W': newY--; break;
    case 'S': newY++; break;
    case 'A': newX--; break;
    case 'D': newX++; break;
    default:
        return false; 
    }

    if (!map.isInside(newX, newY))
        return false;

    if (!map.canEnter(newX, newY))
        return false;

    x = newX;
    y = newY;

    return true;
}

void Hero::drawStatus() const {
    cout << "HP: " << health << "/" << maxHealth
        << "   RANGE: " << attackRange;
}

