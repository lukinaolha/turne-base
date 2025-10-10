#pragma once
#include <string>
#include "Map.h"
using namespace std;

class Enemy {
private:
    string name;     
    int health;      
    int x, y;        

public:
    Enemy(string n = "Goblin", int startX = 5, int startY = 2);

    void takeDamage();           
    bool isAlive() const;        

    int getX() const { return x; }
    int getY() const { return y; }
};
