#pragma once
#include "enemy.h"
#include <string>
#include <cstdlib>

class EnemyFactory {
public:

    static Enemy* createEnemyByType(const std::string& type, int x, int y);

    static Enemy* createRandomEnemy(int x, int y);
};
