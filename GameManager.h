#pragma once
#include "Map.h"
#include "hero.h"
#include "enemy.h"
#include "Chest.h"
using namespace std;

class GameManager {
private:
    Map* map;          // карта як вказівник
    Hero& hero;
    vector<Enemy*> enemies;
    Chest* chest;
    bool gameOver;

    int level = 1;
    int baseW, baseH;

    void spawnEnemies();
    void spawnChest();
    void regenerateLevel();

public:
    GameManager(int width, int height, Hero& heroRef);
    ~GameManager();

    void init();
    void render();
    void update();
    bool isRunning() const;
};
