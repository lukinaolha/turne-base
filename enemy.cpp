#include "enemy.h" 
#include "hero.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Enemy::Enemy(string n, int startX, int startY)
    : Entity(startX, startY),  
    name(n),
    health(1)
{
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
void Goblin::updateAI(int heroX, int heroY, const Map& map) {
    if (!isAlive()) return;

    // Гоблін завжди просто йде до героя (без випадкового блудіння)
    moveTowards(heroX, heroY, map);
}

// ======= Orc =======
void Orc::updateAI(int heroX, int heroY, const Map& map) {
    if (!isAlive()) return;

    // Орк рухається через хід
    if (moveCooldown == 0) {
        moveTowards(heroX, heroY, map);
        moveCooldown = 1;
    }
    else {
        moveCooldown = 0; // цей хід стоїть
    }
}

void Orc::attackHero(Hero& hero) {
    if (!isAlive()) return;
    // Орк б'є сильніше за базового ворога
    hero.takeDamage(1);
}

// ======= Zombie =======
void Zombie::updateAI(int heroX, int heroY, const Map& map) {
    if (!isAlive()) return;

    // 50% — використовує базовий AI (рандом/агро), 50% — стоїть
    if (rand() % 100 < 50) {
        Enemy::updateAI(heroX, heroY, map);
    }
    // інакше зомбі просто стоїть
}