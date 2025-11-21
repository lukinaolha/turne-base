#pragma once
#include <string>
#include "Map.h"
using namespace std;

class Enemy {
private:
    string name;     
    int health;      
    int x, y;       
    int aggroRange = 4;


public:
    Enemy(string n = "Goblin", int startX = 5, int startY = 2);

    void moveTowards(int heroX, int heroY, const Map& map);
    void updateAI(int heroX, int heroY, const Map& map);
    void takeDamage();
    bool isAlive() const;        

    int getX() const { return x; }
    int getY() const { return y; }
};
