#pragma once
#include "Map.h"
#include "hero.h"
#include "enemy.h"
using namespace std;

class GameManager {
private:
    Map map;
    Hero& hero;
    vector<Enemy*> enemies;
    bool gameOver;

public:
    GameManager(int width, int height, Hero& heroRef);

    void init();
    void render();
    void update();
    bool isRunning() const;
};
