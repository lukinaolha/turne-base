#include "enemy.h" 
#include <iostream>
#include <cstdlib>
using namespace std;

Enemy::Enemy(string n, int startX, int startY)
    : name(n), health(1), x(startX), y(startY) {
}

void Enemy::moveTowards(int heroX, int heroY, const Map& map) {
    if (!isAlive()) return;
    int dx = heroX - x;
    int dy = heroY - y;

    int nx = x;
    int ny = y;

    if (abs(dx) > abs(dy)) {
        nx += (dx > 0 ? 1 : -1);
    }

    else if (abs(dy) > abs(dx)) {
        ny += (dy > 0 ? 1 : -1);
    }

    else {
        if (rand() % 2 == 0)
            nx += (dx > 0 ? 1 : -1);
        else
            ny += (dy > 0 ? 1 : -1);
    }

    if (map.isInside(nx, ny) && map.canEnter(nx, ny)) {

        if (nx == heroX && ny == heroY)
            return;

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

            if (nx == heroX && ny == heroY)
                return;

            x = nx;
            y = ny;
        }
        return;
    }

    moveTowards(heroX, heroY, map);
}

void Enemy::attackHero(Hero& hero) {
    if (!isAlive()) return;

    hero.takeDamage(1); 
}

void Enemy::takeDamage() {
    health = 0;
}

bool Enemy::isAlive() const {
    return health > 0;
}
