#pragma once
#include <string>
#include "Map.h"
using namespace std;

class Hero {
private:
    string name;
    int health;
    int maxHealth;
    int attackRange;
    int x, y;

public:
    Hero(string n = "User", int hp = 3, int range = 1, int startX = 0, int startY = 0);

    bool move(char direction, const Map& map);
    void drawStatus() const;

    int getX() const { return x; }
    int getY() const { return y; }
};


