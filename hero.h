#pragma once
#include <string>
#include "Map.h"
#include "Move.h"
using namespace std;

class Hero {
private:
    string name;
    int health;
    int maxHealth;
    int attackRange;
    int x, y;
    Move moveController; 

public:
    Hero();

    Hero(string n, int hp, int range, int startX, int startY);

    bool move(Direction dir, const Map& map);

    void drawStatus() const;

    int getX() const { return x; }
    int getY() const { return y; }
};
