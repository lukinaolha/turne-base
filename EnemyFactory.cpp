#include "EnemyFactory.h"
#include "enemy.h"
#include <ctime>

Enemy* EnemyFactory::createEnemyByType(const std::string& type, int x, int y) {
    if (type == "Goblin") return new Goblin(x, y);
    if (type == "Orc")    return new Orc(x, y);
    if (type == "Zombie") return new Zombie(x, y);

    return nullptr;
}

Enemy* EnemyFactory::createRandomEnemy(int x, int y) {
    int r = rand() % 3;

    switch (r) {
    case 0: return new Goblin(x, y);
    case 1: return new Orc(x, y);
    case 2: return new Zombie(x, y);
    }
    return nullptr;
}
