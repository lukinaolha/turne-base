#include "enemy.h"
#include <iostream>
using namespace std;

Enemy::Enemy(string n, int startX, int startY)
    : name(n), health(1), x(startX), y(startY) {
}

void Enemy::takeDamage() {
    health = 0;
}

bool Enemy::isAlive() const {
    return health > 0;
}
