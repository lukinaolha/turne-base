#pragma once
#include "Map.h"
#include "hero.h"
#include "enemy.h"

class GameManager {
private:
    Map map;
    Hero* hero;
    Enemy* enemy;
    bool gameOver;

public:
    GameManager(int width = 10, int height = 10);

    void init();      
    void render();   
    void update();    
    bool isRunning() const;
};