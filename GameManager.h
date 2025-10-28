#pragma once
#include "Map.h"
#include "hero.h"
#include "enemy.h"
using namespace std;

class GameManager {
private:
    Map map;
    Hero* hero;
    vector<Enemy*> enemies;  
    bool gameOver;

public:
    GameManager(int width = 10, int height = 10);

    void init();      
    void render();   
    void update();    
    bool isRunning() const;
};