#pragma once
#include "Map.h"
#include "hero.h"
#include "enemy.h"
#include "Chest.h"
#include <vector>
using namespace std;

class GameManager {
private:

    Map* map;                
    Hero& hero;              
    vector<Enemy*> enemies;   
    Chest* chest;            
    bool gameOver;          

    int level = 1;          
    int baseW, baseH;         

    void spawnEnemies();      
    void spawnChest();        
    void regenerateLevel();   

    bool isEnemyAt(int x, int y) const;   

public:

    GameManager(int width, int height, Hero& heroRef);
    ~GameManager();

    void init();   
    void render();   
    void update();  
    bool isRunning() const;  
};
