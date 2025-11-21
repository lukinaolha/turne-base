#include "enemy.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Enemy::Enemy(string n, int startX, int startY)
    : name(n), health(1), x(startX), y(startY) {
}

void Enemy::moveTowards(int heroX, int heroY, const Map& map) {
    if (!isAlive()) return;

    int dx = 0;
    int dy = 0;

    if (heroX > x) dx = 1;
    else if (heroX < x) dx = -1;

    if (heroY > y) dy = 1;
    else if (heroY < y) dy = -1;

    int nx = x + dx;
    int ny = y + dy;

    if (map.isInside(nx, ny) && map.canEnter(nx, ny)) {
        x = nx;
        y = ny;
    }
}

void Enemy::updateAI(int heroX, int heroY, const Map& map) {
    if (!isAlive()) return;

    int dx = abs(heroX - x);
    int dy = abs(heroY - y);

    if (dx + dy > aggroRange) {

        if (rand() % 100 < 30) return;

        int dir = rand() % 4;
        int nx = x, ny = y;

        switch (dir) {
        case 0: ny--; break;
        case 1: ny++; break;
        case 2: nx--; break;
        case 3: nx++; break;
        }

        if (map.isInside(nx, ny) && map.canEnter(nx, ny)) {
            x = nx;
            y = ny;
        }
        return;
    }

    moveTowards(heroX, heroY, map);
}

void Enemy::takeDamage() {
    health = 0;
}

bool Enemy::isAlive() const {
    return health > 0;
}
